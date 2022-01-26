#ifndef SRC_STATES_HPP
#define SRC_STATES_HPP

#define SFML_STATIC

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <memory>
#include <stack>
#include <string>

template<typename T>
using Dictionary = std::map<std::string, T>;

class State
{
protected:
    void loadTexture(const std::string &p_keyName, const std::string &p_fileName);
    void loadFont(const std::string &p_keyName, const std::string &p_fileName);
    void customizeText(const std::string &p_keyName, float p_x, float p_y);
    void loadSoundBuffer(const std::string &p_keyName, const std::string &p_fileName);
    void openMusic(const std::string &p_keyName, const std::string &p_fileName);

public:
    State(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states,
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics);

    virtual void checkEvents(sf::Event &p_event) { }
    virtual void update() = 0;
    virtual void draw() = 0;

protected:
    sf::RenderWindow &m_window;
    std::stack<std::unique_ptr<State>> &m_states;
    
    // Resources
    Dictionary<sf::Texture> &m_textures;
    Dictionary<sf::Font> &m_fonts;
    Dictionary<sf::SoundBuffer> &m_buffers;

    Dictionary<sf::Sprite> &m_sprites;
    Dictionary<sf::Text> &m_texts;
    Dictionary<sf::Sound> &m_sounds;
    Dictionary<sf::Music> &m_musics;
};

#endif // SRC_STATES_HPP
