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
    randomLocation();
    soundManager = &SoundManager::instance(); // Use the singleton instance
}
//===============================================
void Enemy::update(float deltaTime, LevelManager& levelManager) {

    if (m_isFrozen) {
        m_freezeTimeLeft -= deltaTime;
        if (m_freezeTimeLeft <= 0) {
            m_isFrozen = false;
        }
        return;  
    }

    sf::Vector2f movement = m_currentDirection * getSpeed() * deltaTime;
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    sf::Vector2f newPosition = getPosition() + movement;

    
    if (!MoveableObject::isValidPosition(newPosition,levelManager)) {
        changeDirection();
        return; 
    }

    tryMove(movement, levelManager);
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
void Enemy::collide(GameObject& other) {
    other.collide(*this);
}



void Enemy::collide(Player& other)  {
    //resetLocation();
	/*other.undoMove();
	other.setActive(false);*/
	other.setStatus(false);
	//other.setLives(other.getLives() - 1);

}

void Enemy::collide(Enemy& other)  {
    
}

void Enemy::collide(SmartEnemy& other) {

}


void Enemy::collide(Wall& other) {
	randomLocation();
}


void Enemy::collide(Rock& other)  {
	randomLocation();
}

void Enemy::collide(Door& other)  {
    undoMove();
	randomLocation();
}

void Enemy::collide(Explosion& other)  {
    this->setActive(false);
	//add score to the player


}
//===============================================
void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}
//===============================================

void Enemy::resetLocation() {
    for (Enemy* enemy : allEnemies) {
        if (enemy->isActive()) {
            enemy->setPosition(enemy->m_startPosition);
        }
    }
}
//===============================================

void Enemy::freeze(float duration) {
    m_isFrozen = true;
    m_freezeTimeLeft = duration;
}
//===============================================
