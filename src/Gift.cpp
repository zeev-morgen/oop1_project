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

void Gift::collide(GameObject& other, float deltaTime, LevelManager& levelManager)  {
    other.collide(*this, deltaTime, levelManager);
}

void Gift::collide(Enemy& enemy, float deltaTime, LevelManager& levelManager)  {

}

void Gift::collide(Wall& wall, float deltaTime, LevelManager& levelManager)  {

}

//void Gift::collide(Rock& rock, float deltaTime, LevelManager& levelManager)  {
//
//}

void Gift::collide(Door& door, float deltaTime, LevelManager& levelManager)  {

}

void Gift::collide(Explosion& explosion, float deltaTime, LevelManager& levelManager)  {

}

void Gift::collide(Player& player, float deltaTime, LevelManager& levelManager) {
	m_isActive = false;
}
