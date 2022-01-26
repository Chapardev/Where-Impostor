#include "State.hpp"

void State::loadTexture(const std::string &p_keyName, const std::string &p_fileName)
{
    if (!m_textures[p_keyName].loadFromFile(p_fileName))
    {
        throw "Unable to load \"" + p_keyName + "\" texture (path: \"" + p_fileName + "\")";
    }
}

void State::loadFont(const std::string &p_keyName, const std::string &p_fileName)
{
    if (!m_fonts[p_keyName].loadFromFile(p_fileName))
    {
        throw "Unable to load \"" + p_keyName + "\" font (path: \"" + p_fileName + "\")";
    }
}

void State::customizeText(const std::string &p_keyName, float p_x, float p_y)
{
    m_texts.at(p_keyName).setPosition(p_x, p_y);
    m_texts.at(p_keyName).setOutlineThickness(2.f);
    m_texts.at(p_keyName).setOutlineColor(sf::Color::Black);
}

void State::loadSoundBuffer(const std::string &p_keyName, const std::string &p_fileName)
{
    if (!m_buffers[p_keyName].loadFromFile(p_fileName))
    {
        throw "Unable to load \"" + p_keyName + "\" sound (path: \"" + p_fileName + "\")";
    }
}

void State::openMusic(const std::string &p_keyName, const std::string &p_fileName)
{
    if (!m_musics[p_keyName].openFromFile(p_fileName))
    {
        throw "Unable to load \"" + p_keyName + "\" music (path: \"" + p_fileName + "\")";
    }
}

State::State(sf::RenderWindow &p_window, std::stack<std::unique_ptr<State>> &p_states, 
        Dictionary<sf::Texture> &p_textures, 
        Dictionary<sf::Font> &p_fonts,
        Dictionary<sf::SoundBuffer> &p_buffers,
        Dictionary<sf::Sprite> &p_sprites, 
        Dictionary<sf::Text> &p_texts, 
        Dictionary<sf::Sound> &p_sounds,
        Dictionary<sf::Music> &p_musics)
    : m_window { p_window }, m_states { p_states }, m_textures { p_textures }, m_fonts { p_fonts }, m_buffers { p_buffers }, 
      m_sprites { p_sprites }, m_texts { p_texts }, m_sounds { p_sounds }, m_musics { p_musics }
{
    
}
