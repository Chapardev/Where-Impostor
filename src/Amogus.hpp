#ifndef SRC_AMOGUS_HPP
#define SRC_AMOGUS_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;

class Amogus : public sf::Drawable
{
public:
    Amogus() = default;
    Amogus(const sf::Texture &p_texture);

    sf::Color getColor() const noexcept
    {
        return m_colorBody.getColor();
    }

    sf::FloatRect getBounds() const noexcept
    {
        return m_outlineBody.getGlobalBounds();
    }

    void setPosition(float p_x, float p_y);
    void setColor(const sf::Color &p_color);

    void move(const sf::RenderTarget &p_target, float p_dt);

    void draw(sf::RenderTarget &p_target, sf::RenderStates p_states) const override;

private:
    static constexpr float s_speed { 100.f };
    sf::Sprite m_colorBody;
    sf::Sprite m_outlineBody;
    sf::Vector2f m_velocity { Random::get<bool>() ? s_speed : -s_speed, Random::get<bool>() ? s_speed : -s_speed };
};

#endif // SRC_AMOGUS_HPP
