#include "Rock.h"

Rock::Rock(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
}

//need to chack if can delete this function
void Rock::update(float deltaTime, LevelManager& levelManager) {

}

void Rock::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite); 
}

//need to chack if can delete this function
void Rock::collide(Player& player) {
    //player.undoMove();
}

void Rock::collide(Enemy& enemy) {
	enemy.undoMove();
}

void Rock::collide(Explosion& exp) {
	m_isActive = false;
}