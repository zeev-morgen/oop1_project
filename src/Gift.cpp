#include "Gift.h"
#include <iostream>

Gift::Gift(const sf::Texture& texture, const sf::Vector2f& position)
	: StaticObject(texture, position)
{
}

void Gift::update(float deltaTime, LevelManager& levelManager) {
    // עדכון כללי למתנות אם צריך
}

void Gift::draw(sf::RenderWindow& window) const  {
	if (m_show) {
		window.draw(m_sprite);
	}
}

void Gift::collide(GameObject& other)  {
    other.collide(*this); 
}

void Gift::collide(Enemy& enemy)  {

}

void Gift::collide(Wall& wall)  {

}

void Gift::collide(Rock& rock)  {

}

void Gift::collide(Door& door)  {

}

void Gift::collide(Explosion& explosion)  {

}

void Gift::collide(Player& player) {
	m_isActive = false;
}
