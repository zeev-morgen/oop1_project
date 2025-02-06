#include "Enemy.h"
#include "Wall.h"
#include "LevelManager.h"
#include <iostream>

std::vector<Enemy*> Enemy::allEnemies;

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position)
	: MoveableObject(texture, position, ENEMY_SPEED), m_startPosition(position)
{
    allEnemies.push_back(this);
    randomLocation();
}
//===============================================
void Enemy::update(float deltaTime, LevelManager& levelManager) {
    sf::Vector2f movement = m_currentDirection * getSpeed() * deltaTime;
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    sf::Vector2f newPosition = getPosition() + movement;
    
    if (!MoveableObject::isValidPosition(newPosition,levelManager)) {
        changeDirection(deltaTime,levelManager);
        return; 
    }
    
    tryMove(movement, levelManager);
}


//===============================================

void Enemy::changeDirection(float deltaTime, LevelManager& levelManager) {
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
	other.setActive(false);
	//other.setLives(other.getLives() - 1);

}

void Enemy::collide(Enemy& other)  {
    
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
    this->setActive(false);  // ðäøñ îôéöåõ

}

void Enemy::draw(sf::RenderWindow& window) const  {
    window.draw(m_sprite);
}


void Enemy::resetLocation() {
    for (Enemy* enemy : allEnemies) {
        if (enemy->isActive()) {
            enemy->setPosition(enemy->m_startPosition);
        }
    }
}

