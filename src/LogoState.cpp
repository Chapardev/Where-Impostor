#include "LogoState.hpp"

#include "MenuState.hpp"

LogoState::LogoState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics)
    : State { p_window, p_states, p_textures, p_fonts, p_buffers, p_sprites, p_texts, p_sounds, p_musics }
{
    this->loadTexture("background", "../assets/images/planet.png");
    this->loadTexture("logo", "../assets/images/logo.png");

    this->loadFont("press_start", "../assets/fonts/PressStart2P.ttf");

    m_sprites.emplace("background", p_textures.at("background"));
    m_sprites.emplace("logo", p_textures.at("logo"));

    m_texts["logo"] = sf::Text { "Made with", m_fonts.at("press_start") };
    this->customizeText(
        "logo",
        (m_window.getSize().x - m_texts.at("logo").getGlobalBounds().width) / 2.f - m_texts.at("logo").getGlobalBounds().height,
        (m_window.getSize().y - m_texts.at("logo").getGlobalBounds().height) / 2.f - m_texts.at("logo").getGlobalBounds().height * 1.5f
    );

    m_sprites.at("logo").setPosition(
        (m_window.getSize().x - m_sprites.at("logo").getGlobalBounds().width) / 2.f,
        m_texts.at("logo").getGlobalBounds().top + m_texts.at("logo").getGlobalBounds().height + 20
    );
}

void LogoState::update()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || m_clock.getElapsedTime().asSeconds() > 2.f)
    {
        m_states.push(std::make_unique<MenuState>(m_window, m_states, m_textures, m_fonts, m_buffers, m_sprites, m_texts, m_sounds, m_musics));
    }
}

void LogoState::draw()
{
    m_window.draw(m_sprites.at("background"));
    m_window.draw(m_texts.at("logo"));
    m_window.draw(m_sprites.at("logo"));
}
