#include "Door.h"

Door::Door(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
}

void Door::collide(GameObject& other) {
    other.collide(*this);  // Double dispatch
}


void Door::collide(Enemy& other) {
    undoMove();  // נתקע באויב
    // טיפול בפגיעה
}

void Door::collide(Player& other) {
    undoMove();  // נתקע בקיר
}

void Door::collide(Explosion& other) {
    undoMove();  // נתקע באבן
}