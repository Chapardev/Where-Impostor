#include "Amogus.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Amogus::Amogus(const sf::Texture &p_texture)
    : m_colorBody { p_texture, { 0, 0, 50, 50 } }, m_outlineBody { p_texture, { 50, 0, 50, 50 } }
{
    
}

void Amogus::move(const sf::RenderTarget &p_target, float p_dt)
{
    m_colorBody.move(m_velocity * p_dt);
    m_outlineBody.move(m_velocity * p_dt);

    if (m_outlineBody.getGlobalBounds().left < 0)
    {
        this->setPosition(0, m_outlineBody.getPosition().y);
        m_velocity.x = -m_velocity.x;
    }
    else if (m_outlineBody.getGlobalBounds().left + m_outlineBody.getGlobalBounds().width > p_target.getSize().x)
    {
        this->setPosition(p_target.getSize().x - m_outlineBody.getGlobalBounds().width, m_outlineBody.getPosition().y);
        m_velocity.x = -m_velocity.x;
    }

    if (m_outlineBody.getGlobalBounds().top < 0)
    {
        this->setPosition(m_outlineBody.getPosition().x, 0);
        m_velocity.y = -m_velocity.y;
    }
    else if (m_outlineBody.getGlobalBounds().top + m_outlineBody.getGlobalBounds().height > p_target.getSize().y - 100.f)
    {
        this->setPosition(m_outlineBody.getPosition().x, p_target.getSize().y - 100.f - m_outlineBody.getGlobalBounds().height);
        m_velocity.y = -m_velocity.y;
    }
}

void Amogus::setPosition(float p_x, float p_y)
{
    m_colorBody.setPosition(p_x, p_y);
    m_outlineBody.setPosition(p_x, p_y);
}

void Amogus::setColor(const sf::Color &p_color)
{
    m_colorBody.setColor(p_color);
}

void Amogus::draw(sf::RenderTarget &p_target, sf::RenderStates p_states) const
{
    p_target.draw(m_colorBody);
    p_target.draw(m_outlineBody);
}
