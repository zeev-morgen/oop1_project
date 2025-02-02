#include "Rock.h"

Rock::Rock(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
}

void Rock::update(float deltaTime, LevelManager& levelManager) {

}

void Rock::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite); 
}