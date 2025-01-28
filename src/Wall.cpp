#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Rock.h"

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
    // הגדרות ספציפיות לקיר אם יש
}

void Wall::collide(GameObject& other)  {
    other.collide(*this);
}

void Wall::collide(Player& player)  {
    //player.undoMove();
}

void Wall::collide(Enemy& enemy)  {
    enemy.undoMove();
}

void Wall::collide(Explosion& explosion)  {
    // קירות לא מושפעים מפיצוצים
}