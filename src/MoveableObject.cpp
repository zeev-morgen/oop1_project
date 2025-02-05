#include "MoveableObject.h"
#include "LevelManager.h"
#include <iostream>

class LevelManager;

MoveableObject::MoveableObject(const sf::Texture& texture, const sf::Vector2f& position, float speed)
	: GameObject(texture, position),
	m_speed(speed),
	m_isMoving(false)
{
	m_direction = {0.f, 0.f};
}
//===============================================
void MoveableObject::move(const sf::Vector2f& movement) {
	sf::Vector2f currentPos = getPosition();
	setPosition(currentPos + movement);
}
//===============================================
void MoveableObject::setDirection(sf::Vector2f direction) {
	m_direction = direction;
	m_isMoving = (direction.x != 0.f || direction.y != 0.f);  
}
//===============================================
void MoveableObject::stop() {
	m_isMoving = false;
	m_direction = { 0.f, 0.f };
}
//===============================================
void MoveableObject::setSpeed(float speed){
	m_speed = speed;
}
//===============================================
float MoveableObject::getSpeed()const {
	return m_speed;
}
//===============================================
bool MoveableObject::isValidPosition(const sf::Vector2f& newPosition, LevelManager& levelManager)  {
    
	return (newPosition.x <= levelManager.getCols() * Config::TILE_HEIGHT - Config::TILE_HEIGHT
        && newPosition.x >= 0 
        && newPosition.y <= levelManager.getRows() * Config::TILE_HEIGHT - Config::TILE_HEIGHT + Config::UI
        && newPosition.y >= Config::UI);
}

//===============================================
void MoveableObject::tryMove(const sf::Vector2f& movement, LevelManager& levelManager) {
    sf::Vector2f newPosition = getPosition() + movement;

    if (newPosition.x < 0) {
        newPosition.x = 0;
    }

    else if (newPosition.x > (levelManager.getCols() - 1) * Config::TILE_HEIGHT) {
        newPosition.x = (levelManager.getCols() - 1) * Config::TILE_HEIGHT;
    }

    if (newPosition.y < Config::UI) {
        newPosition.y = Config::UI;
    }

    else if (newPosition.y > (levelManager.getRows() - 1) * Config::TILE_HEIGHT + Config::UI) {
        newPosition.y = (levelManager.getRows() - 1) * Config::TILE_HEIGHT + Config::UI;
    }

    if (newPosition != getPosition()) {
        m_prevPosition = getPosition();
        setPosition(newPosition);
        m_isMoving = true;  // השחקן בתנועה
    }
    else {
        // אם השחקן לא זז (אין תנועה חדשה)
        if (m_isMoving) {
            // השחקן הפסיק לנוע - נבצע יישור למשבצת
            alignToTile();
            m_isMoving = false;
        }
    }
}
//===============================================

void MoveableObject::collide(GameObject& other) {
    other.collide(*this);
}
//===============================================
void MoveableObject::alignToTile() {
    sf::Vector2f currentPos = getPosition();

    // חישוב המשבצת הקרובה ביותר
    float tileX = std::round(currentPos.x / Config::TILE_HEIGHT) * Config::TILE_HEIGHT;
    float tileY = std::round(currentPos.y / Config::TILE_HEIGHT) * Config::TILE_HEIGHT;

    // יישור למשבצת
    setPosition({ tileX, tileY });
}
