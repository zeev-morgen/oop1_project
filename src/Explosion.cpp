#include "Explosion.h"

Explosion::Explosion(const sf::Texture& texture, const sf::Vector2f& position, sf::Font font)
    : StaticObject(texture, position) {
}

void Explosion::update(float deltaTime, LevelManager& levelManager) {
    if (m_lifetimeClock.getElapsedTime().asSeconds() >= m_lifetime) {
		m_isActive = false;
    }
}

void Explosion::draw(sf::RenderWindow& window) const {
    if(m_isActive){
		window.draw(m_sprite);
    }
}

void Explosion::collide(GameObject& other, float deltaTime, LevelManager& levelManager) {
	other.collide(*this,  deltaTime,  levelManager);
}

void Explosion::collide(Enemy& other, float deltaTime, LevelManager& levelManager) {
	other.setActive(false);
}

void Explosion::collide(Player& other, float deltaTime, LevelManager& levelManager) {
	other.undoMove();
	other.setActive(false);
}

void Explosion::collide(Explosion& other, float deltaTime, LevelManager& levelManager) {

}

void Explosion::collide(Rock& other, float deltaTime, LevelManager& levelManager) {
	other.setActive(false);


}
