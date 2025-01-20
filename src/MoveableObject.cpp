#include "MoveableObject.h"

MoveableObject::MoveableObject(const sf::Texture& texture, const sf::Vector2f& position, float speed)
	: GameObject(texture, position),
	m_speed(speed),
	m_isMoving(false)
{
	m_direction = {0.f, 0.f};
}

void MoveableObject::move(const sf::Vector2f& movement) {
	sf::Vector2f currentPos = getPosition();
	setPosition(currentPos + movement);
}

void MoveableObject::setDirection(sf::Vector2f direction) {
	m_direction = direction;
	m_isMoving = (direction.x != 0.f || direction.y != 0.f);  // הוסף שורה זו
}

void MoveableObject::stop() {
	m_isMoving = false;
	m_direction = { 0.f, 0.f };
}

void MoveableObject::setSpeed(float speed){
	m_speed = speed;
}

float MoveableObject::getSpeed()const {
	return m_speed;
}

bool MoveableObject::isValidPosition(const sf::Vector2f& pos) const{
    if (pos.x < 0.f || pos.x > 800.f - 32.f ||
        pos.y < 0.f || pos.y > 600.f - 32.f) {
        return false;
    }

    //צריך להוסיף בדיקה עם מכשולים
    return true;
}