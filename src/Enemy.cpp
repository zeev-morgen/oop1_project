#include "Enemy.h"
#include "Wall.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include <iostream>

std::vector<Enemy*> Enemy::allEnemies;

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, ENEMY_SPEED), m_startPosition(position)
{
    allEnemies.push_back(this);
    //setOrigin();
    randomLocation();
    soundManager = &SoundManager::instance(); // Use the singleton instance
}
//===============================================
void Enemy::update(float deltaTime, LevelManager& levelManager) {
    sf::Vector2f movement = m_currentDirection * getSpeed() * deltaTime;
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    sf::Vector2f newPosition = getPosition() + movement;

    if (!MoveableObject::isValidPosition(newPosition, levelManager)) {
        changeDirection(deltaTime, levelManager);
        return;
    }

    tryMove(movement, levelManager);
}

//===============================================
void Enemy::changeDirection(float deltaTime, LevelManager& levelManager) {
    const sf::Vector2f possibleDirections[] = {
                {1.0f, 0.0f},   // éîéðä
                {-1.0f, 0.0f},  // ùîàìä
                {0.0f, 1.0f},   // ìîèä
                {0.0f, -1.0f}   // ìîòìä
    };

    // save the current direction
    sf::Vector2f oldDirection = m_currentDirection;
    int attempts = 0;
    do {
        int randomIndex = rand() % 4; // áçø ëéååï à÷øàé îúåê äàôùøåéåú
        m_currentDirection = possibleDirections[randomIndex];
        attempts++;
        // áî÷øä åàéï ëéååï ú÷éï ìàçø îñôø ðéñéåðåú, ùîåø òì äëéååï ä÷åãí
        if (attempts > 2) {
            m_currentDirection = oldDirection;
            break;
        }
    } while (!MoveableObject::isValidPosition(getPosition() + (m_currentDirection * getSpeed() * deltaTime), levelManager));
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
void Enemy::collide(GameObject& other, float deltaTime, LevelManager& levelManager) {
    other.collide(*this, deltaTime, levelManager);
}

void Enemy::collide(Player& other, float deltaTime, LevelManager& levelManager) {
    other.setActive(false);
}

void Enemy::collide(Enemy& other, float deltaTime, LevelManager& levelManager) {
    // àåéáéí òåáøéí àçã ãøê äùðé
}

void Enemy::collide(Wall& other, float deltaTime, LevelManager& levelManager) {
    changeDirection(deltaTime, levelManager);
}

void Enemy::collide(Rock& other, float deltaTime, LevelManager& levelManager) {
    changeDirection(deltaTime, levelManager);  // ðú÷ò áàáï
}

void Enemy::collide(Door& other, float deltaTime, LevelManager& levelManager) {
    undoMove();  // ðú÷ò áãìú
}

void Enemy::collide(Explosion& other, float deltaTime, LevelManager& levelManager) {
    this->setActive(false);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

//ôåð÷öééä ìäçæøú ùåîøéí ìîé÷åí äúçìúé
void Enemy::resetLocation() {
    for (Enemy* enemy : allEnemies) {
        if (enemy->isActive()) {
            enemy->setPosition(enemy->m_startPosition);
        }
    }
}
