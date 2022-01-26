#ifndef SRC_GAME_HPP
#define SRC_GAME_HPP

#include "LogoState.hpp"

#include <array>

class Game
{
public:
    static std::string getCurrentDateTime() noexcept;
    static void logError(const std::string &message);

private:
    void _loadImage(sf::Image &p_image, const std::string &p_fileName) const;

public:
    Game();

    bool isRunning() const noexcept { return m_window.isOpen(); }

    void pollEvents();
    void update();
    void draw();

private:
    sf::RenderWindow m_window { { 600, 600+100 }, "Where Impostor", sf::Style::Titlebar | sf::Style::Close };
    std::stack<std::unique_ptr<State>> m_states;
    
    // Graphics resources
    Dictionary<sf::Texture> m_textures;
    Dictionary<sf::Sprite> m_sprites;
    Dictionary<sf::Font> m_fonts;
    Dictionary<sf::Text> m_texts;

    // Audio resources
    Dictionary<sf::SoundBuffer> m_buffers;
    Dictionary<sf::Sound> m_sounds;
    Dictionary<sf::Music> m_musics;
};

#endif // SRC_GAME_HPP
