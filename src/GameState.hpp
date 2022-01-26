#ifndef SRC_GAME_STATE_HPP
#define SRC_GAME_STATE_HPP

#include "State.hpp"

#include "Amogus.hpp"

#include <array>

class GameState : public State
{
public:
    GameState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics);
    
    void loadAssets();

    // Place randomly the characters
    void placeAmoguses();

    bool isOver() const noexcept
    {
        return (m_lives == 0) || (m_timeMax - m_clockCounter.getElapsedTime().asSeconds() < 0.f);
    }

    void checkEvents(sf::Event &p_event) override;
    void update() override;
    void draw() override;

private:
    static constexpr size_t s_numberOfAmoguses { 150 };
    std::array<Amogus, s_numberOfAmoguses> m_amoguses;

    sf::FloatRect m_mouseRect { 0.f, 0.f, 150.f, 150.f };
    std::array<sf::RectangleShape, 4> m_borders;

    static constexpr float m_timeMax { 30.f + 1.f };
    sf::Clock m_clockCounter;

    sf::RectangleShape m_alertRect;
    sf::Clock m_alertClock;

    sf::Clock m_dtClock;
    float m_dt;

    sf::Clock m_gameOverClock;
    bool m_clockRestartedOnce;

    const std::array<sf::Color, 18> m_colors {
        sf::Color::White,
        sf::Color::Black, 
        sf::Color::Cyan,
        sf::Color::Green,
        sf::Color { 179, 10, 31 }, // red
        sf::Color { 19, 47, 210 }, // blue
        sf::Color { 18, 127, 45 }, // dark green
        sf::Color { 237, 83, 185 }, // pink
        sf::Color { 239, 125, 14 }, // orange
        sf::Color { 246, 246, 49 }, // yellow
        sf::Color { 107, 50, 188 }, // purple
        sf::Color { 114, 73, 30 }, // brown
        sf::Color { 107, 43, 60 }, // marron
        sf::Color { 236, 192, 111 }, // rose
        sf::Color { 255, 254, 190 }, // banana
        sf::Color { 112, 132, 150 }, // gray
        sf::Color { 146, 135, 118 }, // tan
        sf::Color { 236, 117, 120 }, // coral
    };

    Amogus m_impostor;
    int m_impostorsFound;

    static constexpr std::size_t m_totalLives { 3 };
    std::size_t m_lives;
    std::array<sf::Sprite, m_totalLives> m_emptyHearts;
    std::array<sf::Sprite, m_totalLives> m_hearts;
};

#endif // SRC_GAME_STATE_HPP
