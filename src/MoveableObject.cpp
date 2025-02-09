#include "MoveableObject.h"
#include "LevelManager.h"
#include <iostream>
#include <cmath>

class LevelManager;

MoveableObject::MoveableObject(const sf::Texture& texture, const sf::Vector2f& position, float speed)
	: GameObject(texture, position),
	m_speed(speed),
	m_isMoving(false),
	m_isFrozen(false)
{
	m_freezeTime = Config::FREEZE_DURATION;
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

//void MoveableObject::tryMove(const sf::Vector2f& movement, LevelManager& levelManager) {
//    sf::Vector2f newPosition = getPosition() + movement;
//    bool wasBlocked = false;
//
//    // בדיקת גבולות המסך
//    if (newPosition.x < 0) {
//        newPosition.x = 0;
//        wasBlocked = true;
//    }
//    else if (newPosition.x > (levelManager.getCols() - 1) * Config::TILE_HEIGHT) {
//        newPosition.x = (levelManager.getCols() - 1) * Config::TILE_HEIGHT;
//        wasBlocked = true;
//    }
//
//    if (newPosition.y < Config::UI) {
//        newPosition.y = Config::UI;
//        wasBlocked = true;
//    }
//    else if (newPosition.y > (levelManager.getRows() - 1) * Config::TILE_HEIGHT + Config::UI) {
//        newPosition.y = (levelManager.getRows() - 1) * Config::TILE_HEIGHT + Config::UI;
//        wasBlocked = true;
//    }
//
//    // שמירת המיקום הקודם לפני העדכון
//    m_prevPosition = getPosition();
//
//    // עדכון המיקום החדש
//    setPosition(newPosition);
//
//    // עדכון סטטוס התנועה
//    m_isMoving = (newPosition != m_prevPosition);
//    m_isBlocked = wasBlocked;
//}

//===============================================

//void MoveableObject::collide(GameObject& other) {
//    other.collide(*this);
//}
//===============================================
void MoveableObject::alignToTile() {
    sf::Vector2f currentPos = getPosition();

    /*tileX = currentPos.x;
	tileY = currentPos.y;*/

    //חישוב משבצת קרובה ב 10 פיקסלים
    //תיקון רק ב 10 פיקסלים



    // חישוב המשבצת הקרובה ביותר
    float tileX = std::round(currentPos.x / Config::TILE_HEIGHT) * Config::TILE_HEIGHT;
    float tileY = std::round(currentPos.y / Config::TILE_HEIGHT) * Config::TILE_HEIGHT;
    
    // יישור למשבצת
    setPosition({ tileX, tileY });
}
//===============================================
bool MoveableObject::isBlocked() const {
    return m_isBlocked; 
}
//===============================================
void MoveableObject::changeDirection(float deltaTime, LevelManager& levelManager) {
    const sf::Vector2f possibleDirections[] = {
                {1.0f, 0.0f},
                {-1.0f, 0.0f},
                {0.0f, 1.0f},
                {0.0f, -1.0f}
    };

    // save the current direction
    sf::Vector2f oldDirection = m_currentDirection;
    int attempts = 0;

    // do {
    int randomIndex = rand() % 4;
    m_currentDirection = possibleDirections[randomIndex];
    attempts++;

    if (attempts > 2) {
        m_currentDirection = oldDirection;
        // break;
    }
    // } while (!MoveableObject::isValidPosition(getPosition() + (m_currentDirection * getSpeed() * deltaTime), levelManager));
}
