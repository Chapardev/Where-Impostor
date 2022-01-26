#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics)
    : State { p_window, p_states, p_textures, p_fonts, p_buffers, p_sprites, p_texts, p_sounds, p_musics }, 
      m_alertRect { { m_window.getSize().x * 1.f, m_window.getSize().y - 100.f } },
      m_clockRestartedOnce { false }, m_impostorsFound { 0 }, m_lives { m_totalLives }
{
    m_window.setMouseCursorVisible(false);

    if (m_textures.find("heart") == m_textures.end())
    {
        this->loadAssets();
    }

    m_alertRect.setFillColor({ 255, 0, 0, 128 });

    m_impostor = Amogus { m_textures.at("amogus") };
    m_impostor.setPosition(
        m_window.getSize().x - m_impostor.getBounds().width * 1.5f,
        m_window.getSize().y - m_impostor.getBounds().height * 1.25f
    );

    for (auto &amogus : m_amoguses)
    {
        amogus = Amogus { m_textures.at("amogus") };
    }

    this->placeAmoguses();

    for (std::size_t i { 0 }; i < m_totalLives; ++i)
    {
        m_emptyHearts[i] = sf::Sprite { m_textures.at("heart"), { 0, 0, 35, 35 } };
        m_emptyHearts[i].setPosition(5.f + i * 25.f, m_window.getSize().y - 65.f - m_sprites["heart"].getGlobalBounds().height / 2);

        m_hearts[i] = sf::Sprite { m_textures.at("heart"), { 35, 0, 35, 35 } };
        m_hearts[i].setPosition(m_emptyHearts[i].getPosition());
    }

    if (m_texts.find("time") == m_texts.end())
    {
        m_texts["time"] = sf::Text { "0:00", m_fonts.at("press_start"), 20u };
        this->customizeText("time", 15.f, m_hearts[0].getPosition().y + m_hearts[0].getGlobalBounds().width + 6.f);
    }

    for (auto &border : m_borders)
    {
        border.setFillColor(sf::Color::Black);
    }

    m_musics.at("bg").play();
}

void GameState::loadAssets()
{
    this->loadTexture("heart", "../assets/images/heart.png");
    this->loadTexture("amogus", "../assets/images/amogus.png");
    this->loadTexture("gui_bg", "../assets/images/gui_bg.png");
    this->loadTexture("target", "../assets/images/target.png");

    this->loadSoundBuffer("good_one", "../assets/sounds/shoot.wav");
    this->loadSoundBuffer("bad_one", "../assets/sounds/wrong.wav");
    this->loadSoundBuffer("alert", "../assets/sounds/alert.wav");

    m_sprites.emplace("gui_bg", m_textures.at("gui_bg"));
    m_sprites.at("gui_bg").setPosition(0, m_window.getSize().y - m_sprites.at("gui_bg").getGlobalBounds().height);
    m_sprites.emplace("target", m_textures.at("target"));

    m_sounds.emplace("good_one", m_buffers.at("good_one"));
    m_sounds.emplace("bad_one", m_buffers.at("bad_one"));
    m_sounds.emplace("alert", m_buffers.at("alert"));

    m_texts["game_over"] = sf::Text { "GAME OVER!", m_fonts.at("press_start"), 60u };
    this->customizeText(
        "game_over",
        (m_window.getSize().x - m_texts.at("game_over").getGlobalBounds().width) / 2.f,
        (m_window.getSize().y - m_texts.at("game_over").getGlobalBounds().height) / 2.f
    );

    m_texts["score"] = sf::Text { "000", m_fonts.at("press_start"), 20u };
    this->customizeText("score", 15.f, m_sprites.at("gui_bg").getPosition().y + 11.f);

    if (!m_musics["bg"].openFromFile("../assets/musics/bg.wav"))
    {
        throw std::string{ "Unable to load music" };
    }

    m_musics.at("bg").setLoop(true);
}

void GameState::placeAmoguses()
{
    m_impostor.setColor(*Random::get(m_colors));

    for (auto &amogus : m_amoguses)
    {
        amogus.setColor(m_impostor.getColor());
        while (amogus.getColor() == m_impostor.getColor())
        {
            amogus.setColor(*Random::get(m_colors));
        }

        amogus.setPosition(
            Random::get(0.f, m_window.getSize().x - amogus.getBounds().width), 
            Random::get(0.f, m_sprites.at("gui_bg").getPosition().y - amogus.getBounds().height)
        );
    }

    m_amoguses[0].setColor(m_impostor.getColor());
}

void GameState::checkEvents(sf::Event &p_event)
{
    if (p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::Escape)
    {
        m_window.setMouseCursorVisible(true);
        m_musics.at("bg").stop();
        m_states.pop();
        return;
    }

    if (!this->isOver() && (p_event.type == sf::Event::MouseButtonPressed) && (p_event.mouseButton.button == sf::Mouse::Left))
    {
        if (m_amoguses[0].getBounds().contains(p_event.mouseButton.x, p_event.mouseButton.y))
        {
            ++m_impostorsFound;

            m_sounds.at("good_one").play();

            m_texts.at("score").setString(
                (m_impostorsFound >= 100 ? std::to_string(m_impostorsFound / 100) : "0") 
                + (m_impostorsFound >= 10 ? std::to_string(m_impostorsFound / 10) : "0")
                + std::to_string(m_impostorsFound % 10)
            );

            m_clockCounter.restart();

            this->placeAmoguses();
        }
        else
        {
            int i { 0 };
            for (const auto &amogus : m_amoguses)
            {
                if (amogus.getBounds().contains(p_event.mouseButton.x, p_event.mouseButton.y))
                {
                    m_sounds.at("bad_one").play();
                    if (m_lives > 0)
                    {
                        --m_lives;
                        break;
                    }
                }
                ++i;
            }
        }
    }
}

void GameState::update()
{
    m_dt = m_dtClock.restart().asSeconds();

    m_sprites.at("target").setPosition(
        sf::Mouse::getPosition(m_window).x - m_sprites.at("target").getGlobalBounds().width / 2, 
        sf::Mouse::getPosition(m_window).y - m_sprites.at("target").getGlobalBounds().height / 2
    );

    if (!this->isOver())
    {
        if (m_impostorsFound >= 5)
        {
            if (m_impostorsFound < 10 || (m_impostorsFound >= 15 && m_impostorsFound < 20) || m_impostorsFound >= 25)
            {
                for (auto &amogus : m_amoguses)
                {
                    amogus.move(m_window, m_dt);
                }
            }

            if (m_impostorsFound >= 10)
            {
                if (m_mouseRect.width == 150 && m_impostorsFound >= 20)
                {
                    m_mouseRect.width = 75;
                    m_mouseRect.height = 75;
                }

                m_mouseRect.left = sf::Mouse::getPosition(m_window).x - m_mouseRect.width / 2;
                m_mouseRect.top = sf::Mouse::getPosition(m_window).y - m_mouseRect.height / 2;

                m_borders[0].setSize({ m_mouseRect.left, m_window.getSize().y - m_sprites.at("gui_bg").getGlobalBounds().height });
                m_borders[1].setPosition(m_mouseRect.left + m_mouseRect.width, 0);
                m_borders[1].setSize(
                    { m_window.getSize().x - (m_mouseRect.left + m_mouseRect.width), m_borders[0].getSize().y }
                );
                m_borders[2].setPosition(m_borders[0].getSize().x, 0);
                m_borders[2].setSize({ m_mouseRect.width, m_mouseRect.top });
                m_borders[3].setPosition(m_borders[0].getSize().x, m_mouseRect.top + m_mouseRect.height);
                m_borders[3].setSize({ m_mouseRect.width, m_window.getSize().y - m_sprites.at("gui_bg").getGlobalBounds().height - (m_mouseRect.top + m_mouseRect.height) });
            }
        }

        if (m_timeMax - m_clockCounter.getElapsedTime().asSeconds() < 10.f + 1.f)
        {
            if (m_texts.at("time").getFillColor() != sf::Color::Red)
            {
                m_texts.at("time").setFillColor(sf::Color::Red);
            }

            if (m_alertClock.getElapsedTime().asSeconds() > 2.f)
            {
                if (m_sounds.at("alert").getStatus() != sf::Sound::Playing)
                {
                    m_sounds.at("alert").play();
                }
                m_alertClock.restart();
            }
        }
        else if (m_texts.at("time").getFillColor() != sf::Color::White)
        {
            m_texts.at("time").setFillColor(sf::Color::White);
        }

        m_texts.at("time").setString(
            "0:" + 
            (m_timeMax - m_clockCounter.getElapsedTime().asSeconds() >= 10.f ? 
                std::to_string(static_cast<int>(m_timeMax - m_clockCounter.getElapsedTime().asSeconds()) / 10) : "0"
            ) + std::to_string(static_cast<int>(m_timeMax - m_clockCounter.getElapsedTime().asSeconds()) % 10)
        );
    }
    else
    {
        if (!m_clockRestartedOnce)
        {
            m_gameOverClock.restart();
            m_clockRestartedOnce = true;
            m_musics.at("bg").stop();
            m_sounds.at("lose").play();
        }
        else if (m_gameOverClock.getElapsedTime().asSeconds() > 1.f)
        {
            m_window.setMouseCursorVisible(true);
            m_states.pop();
            return;
        }
    }
}

void GameState::draw()
{
    m_window.draw(m_sprites.at("background"));

    for (const auto &amogus : m_amoguses)
    {
        m_window.draw(amogus);
    }


    if (m_impostorsFound >= 6)
    {
        for (const auto &border : m_borders)
        {
            m_window.draw(border);
        }
    }

    m_window.draw(m_sprites.at("gui_bg"));

    m_window.draw(m_impostor);

    m_window.draw(m_texts.at("score"));

    for (std::size_t i { 0 }; i < m_totalLives; ++i)
    {
        if (i < m_lives)
        {
            m_window.draw(m_hearts[i]);
        }
        else
        {
            m_window.draw(m_emptyHearts[i]);
        }
    }

    m_window.draw(m_texts.at("time"));

    if (this->isOver())
    {
        m_window.draw(m_texts.at("game_over"));
    }

    m_window.draw(m_sprites.at("target"));

    if ((m_timeMax - m_clockCounter.getElapsedTime().asSeconds() < 10.f + 1.f) && (m_alertClock.getElapsedTime().asSeconds() < 1.f))
    {
        m_window.draw(m_alertRect);
    }
}
