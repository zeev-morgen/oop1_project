#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Rock.h"

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
    // הגדרות ספציפיות לקיר אם יש
}

void Wall::collide(GameObject& other, float deltaTime, LevelManager& levelManager)  {
    other.collide(*this, deltaTime ,levelManager);
}

void Wall::collide(Player& player, float deltaTime, LevelManager& levelManager)  {
    //player.undoMove();
}

void Wall::collide(Enemy& enemy, float deltaTime, LevelManager& levelManager)  {
    enemy.undoMove();
}

void Wall::collide(Explosion& explosion, float deltaTime, LevelManager& levelManager)  {
    // קירות לא מושפעים מפיצוצים
}

void Wall::update(float deltaTime, LevelManager& levelManager) {

}

void Wall::draw(sf::RenderWindow& window) const  {
    window.draw(m_sprite);
}