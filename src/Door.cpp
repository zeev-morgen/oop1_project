#include "Door.h"

Door::Door(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
}

void Door::collide(GameObject& other) {
    other.collide(*this);  // Double dispatch
}


void Door::collide(Enemy& other) {
    undoMove();  
}

void Door::collide(Player& other) {
    undoMove();
	//other.m_finishLevel = true;
}

void Door::collide(Explosion& other) {
    undoMove();  // נתקע באבן
}

void Door::update(float deltaTime, LevelManager& levelManager) {

}

void Door::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}
