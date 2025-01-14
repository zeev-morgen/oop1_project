#include "Enemy.h"

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, ENEMY_SPEED)
{
    //setOrigin();
    randomLocation();
}

//===============================================
void Enemy::update(float deltaTime) {

    sf::Vector2f newPos = getPosition() + (m_currentDirection * getSpeed() * deltaTime);

    if (!isValidPosition(newPos)) {
        //if (newPos.x < 0.f || newPos.x > 800.f - 32.f) {
        //    m_currentDirection.x *= -1;  // הפיכת כיוון אופקי
        //}
        //if (newPos.y < 0.f || newPos.y > 600.f - 32.f) {
        //    m_currentDirection.y *= -1;  // הפיכת כיוון אנכי
        //}
        changeDirection(deltaTime);
        newPos = getPosition() + (m_currentDirection * getSpeed() * deltaTime);
    }

	setPosition(newPos);
}

//===============================================
void Enemy::changeDirection(float deltaTime) {
    const sf::Vector2f possibleDirections[] = {
                {1.0f, 0.0f},   // ימינה
                {-1.0f, 0.0f},  // שמאלה
                {0.0f, 1.0f},   // למטה
                {0.0f, -1.0f}   // למעלה
    };

    // save the current direction
    sf::Vector2f oldDirection = m_currentDirection;

    // chake if diferrent diraction
    do {
        int randomIndex = rand() % 4;
        m_currentDirection = possibleDirections[randomIndex];
    } while (!isValidPosition(getPosition() + (m_currentDirection * getSpeed() * deltaTime)));
}

//===============================================
void Enemy::randomLocation() {
    const sf::Vector2f possibleDirections[] = {
                {1.0f, 0.0f}, {-1.0f, 0.0f},
                {0.0f, 1.0f}, {0.0f, -1.0f}
    };
    m_currentDirection = possibleDirections[rand() % 4];
}

//===============================================
