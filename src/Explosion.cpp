#include "Explosion.h"

Explosion::Explosion(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position) {
}

void Explosion::update(float deltaTime, LevelManager& levelManager) {
    if (m_lifetimeClock.getElapsedTime().asSeconds() >= m_lifetime) {
		m_isActive = false;
    }
}

void Explosion::draw(sf::RenderWindow& window) const{
    if(m_isActive){
		window.draw(m_sprite);
    }
}

void Explosion::collide(GameObject& other) {
	other.collide(*this);
}

void Explosion::collide(Enemy& other) {
	other.setActive(false);
}

void Explosion::collide(Player& other) {
	other.undoMove();
	other.setStatus(false);
}

void Explosion::collide(Explosion& other) {

}

void Explosion::collide(Rock& other) {
	other.setActive(false);
}

void Explosion::collide(Wall& wall) {
}

void Explosion::collide(Door& door) {
}

void Explosion::collide(SmartEnemy& smartEnemy) {
	smartEnemy.setActive(false);
}