#include "StaticObject.h"

StaticObject::StaticObject(const sf::Texture& texture, const sf::Vector2f& position)
	: GameObject(texture, position), m_isCollidable(true) {
}

