#include "Game.hpp"

#include "effolkronium/Random.hpp"

#include <ctime>
#include <fstream>

std::string Game::getCurrentDateTime() noexcept
{
    static constexpr const char *format { "%d/%m/%Y ; %X" };
    static constexpr std::size_t bufferSize { sizeof("dd/mm/yyyy ; hh:mm:ss") };

    const std::time_t now { std::time(nullptr) };
    const std::tm tstruct { *std::localtime(&now) };

    static std::array<char, bufferSize> buffer { };
    std::strftime(buffer.data(), buffer.size(), format, &tstruct);

    return buffer.data();
}

void Game::logError(const std::string &message)
{
    std::ofstream ofs { "log.txt", std::ios::app };
    if (ofs.is_open())
    {
        ofs << Game::getCurrentDateTime() << " : " << message << '\n';
    }
}

void Game::_loadImage(sf::Image &p_image, const std::string &p_fileName) const
{
    if (!p_image.loadFromFile(p_fileName))
    {
        throw "Unable to load image \"" + p_fileName + '"';
    }
}

Game::Game()
{
    sf::Image icon;
    this->_loadImage(icon, "../assets/images/icon.png");
    m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    m_states.push(std::make_unique<LogoState>(m_window, m_states, m_textures, m_fonts, m_buffers, m_sprites, m_texts, m_sounds, m_musics));
}

void Game::pollEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        m_states.top()->checkEvents(event);
    }
}

void Game::update()
{
    m_states.top()->update();
}

void Game::draw()
{
    m_window.clear(sf::Color::White);
    
    m_states.top()->draw();

    m_window.display();
}
