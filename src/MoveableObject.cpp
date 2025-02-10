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
    m_direction = { 0.f, 0.f };
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
void MoveableObject::setSpeed(float speed) {
    m_speed = speed;
}
//===============================================
float MoveableObject::getSpeed()const {
    return m_speed;
}
//===============================================
bool MoveableObject::isValidPosition(const sf::Vector2f& position, LevelManager& levelManager) {
    sf::FloatRect newBounds = getGlobalBounds();
    newBounds.left = position.x;
    newBounds.top = position.y;

    for (const auto& obj : levelManager.getGameObjects()) {
        if (auto* wall = dynamic_cast<Wall*>(obj.get())) {
            if (wall->getGlobalBounds().intersects(newBounds)) {
                return false;
            }
        }
        if (auto* rock = dynamic_cast<Rock*>(obj.get())) {
            if (rock->getGlobalBounds().intersects(newBounds)) {
                return false;
            }
        }
        if (auto* door = dynamic_cast<Door*>(obj.get())) {
            if (door->getGlobalBounds().intersects(newBounds)) {
                return false;
            }
        }
    }
    return true;
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
        m_isMoving = true;  // ����� ������
    }
    else {
        // �� ����� �� �� (��� ����� ����)
        if (m_isMoving) {
            // ����� ����� ���� - ���� ����� ������
            alignToTile();
            m_isMoving = false;
        }
    }
}

//===============================================
void MoveableObject::alignToTile() {
    sf::Vector2f currentPos = getPosition();

    /*tileX = currentPos.x;
    tileY = currentPos.y;*/

    //����� ����� ����� � 10 �������
    //����� �� � 10 �������



    // ����� ������ ������ �����
    float tileX = std::round(currentPos.x / Config::TILE_HEIGHT) * Config::TILE_HEIGHT;
    float tileY = std::round(currentPos.y / Config::TILE_HEIGHT) * Config::TILE_HEIGHT;

    // ����� ������
    setPosition({ tileX, tileY });
}
//===============================================
bool MoveableObject::isBlocked() const {
    return m_isBlocked;
}
//===============================================
void MoveableObject::changeDirection() {
    const sf::Vector2f possibleDirections[] = {
                {1.0f, 0.0f},
                {-1.0f, 0.0f},
                {0.0f, 1.0f},
                {0.0f, -1.0f}
    };

    int randomIndex = rand() % 4;
    //m_currentDirection = possibleDirections[randomIndex];
}
//===============================================