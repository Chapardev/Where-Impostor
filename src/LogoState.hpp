#ifndef SRC_LOGO_STATE_HPP
#define SRC_LOGO_STATE_HPP

#include "State.hpp"

class LogoState : public State
{
public:
    LogoState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics);

    void update() override;
    void draw() override;

private:
    sf::Clock m_clock;
};

#endif // SRC_LOGO_STATE_HPP
