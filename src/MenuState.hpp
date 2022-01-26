#ifndef SRC_MENU_STATE_HPP
#define SRC_MENU_STATE_HPP

#include "State.hpp"

class MenuState : public State
{
public:
    MenuState(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics);

    void checkEvents(sf::Event &p_event) override;
    void update() override;
    void draw() override;

private:
    sf::Clock m_clock;
    sf::Clock m_launchClock;
};

#endif // SRC_MENU_STATE_HPP
