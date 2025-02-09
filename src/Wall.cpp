#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Rock.h"
#include "SmartEnemy.h"

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
    // הגדרות ספציפיות לקיר אם יש
}

void Wall::collide(GameObject& other)  {
    other.collide(*this);
}

void Wall::collide(Player& player)  {
    player.undoMove();
}

void Wall::collide(Enemy& enemy)  {
    enemy.undoMove();
}

void Wall::collide(SmartEnemy& smartEnemy) {
    smartEnemy.undoMove();
}

void Wall::collide(Explosion& explosion)  {
    // קירות לא מושפעים מפיצוצים
}

void Wall::collide(Rock& rock) {
}

void Wall::collide(Door& door) {
	// קירות לא מושפעים מדלתות
}

void Wall::collide(Wall& wall) {
	// קירות לא מושפעים מפיצוצים
}

void Wall::update(float deltaTime, LevelManager& levelManager) {

}

void Wall::draw(sf::RenderWindow& window) const  {
    window.draw(m_sprite);
}