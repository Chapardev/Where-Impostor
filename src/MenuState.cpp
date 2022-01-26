#include "MenuState.hpp"

#include "GameState.hpp"

MenuState::MenuState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics)
    : State { p_window, p_states, p_textures, p_fonts, p_buffers, p_sprites, p_texts, p_sounds, p_musics }
{
    this->loadSoundBuffer("lose", "../assets/sounds/lose.wav");
    m_sounds.emplace("lose", m_buffers.at("lose"));
    m_sounds.at("lose").setVolume(50.f);

    m_texts["title"] = sf::Text { "WHERE", p_fonts.at("press_start"), 50u };
    this->customizeText(
        "title",
        (m_window.getSize().x - m_texts.at("title").getGlobalBounds().width) / 2.f, 
        (m_window.getSize().y - m_texts.at("title").getGlobalBounds().height) / 4.f
    );

    m_texts["title2"] = sf::Text { "IMPOSTOR", p_fonts.at("press_start"), 50u };
    this->customizeText(
        "title2",
        (m_window.getSize().x - m_texts.at("title2").getGlobalBounds().width) / 2.f,
        (m_window.getSize().y - m_texts.at("title2").getGlobalBounds().height) / 4.f + m_texts.at("title").getGlobalBounds().height + 20
    );
    m_texts.at("title2").setFillColor(sf::Color::Red);

    m_texts["subtitle"] = sf::Text { "CLICK TO START", p_fonts.at("press_start"), 20u };
    this->customizeText(
        "subtitle",
        (m_window.getSize().x - m_texts.at("subtitle").getGlobalBounds().width) / 2.f, 
        (m_window.getSize().y - m_texts.at("subtitle").getGlobalBounds().height) * (3.f / 4.f)
    );
}

void MenuState::checkEvents(sf::Event &p_event)
{
    if (p_event.type == sf::Event::KeyPressed && p_event.key.code == sf::Keyboard::Escape)
    {
        m_window.close();
    }
}

void MenuState::update()
{
    if (m_clock.getElapsedTime().asSeconds() > 1.f)
    {
        m_clock.restart();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_launchClock.getElapsedTime().asSeconds() > 0.25f)
    {
        if (m_sounds.at("lose").getStatus() == sf::Sound::Playing)
        {
            m_sounds.at("lose").stop();
        }
        m_launchClock.restart();
        m_states.push(std::make_unique<GameState>(m_window, m_states, m_textures, m_fonts, m_buffers, m_sprites, m_texts, m_sounds, m_musics));
    }
}

void MenuState::draw()
{
    m_window.draw(m_sprites.at("background"));

    m_window.draw(m_texts.at("title"));
    m_window.draw(m_texts.at("title2"));

    if (m_clock.getElapsedTime().asSeconds() < 0.5f)
    {
        m_window.draw(m_texts.at("subtitle"));
    }
}
