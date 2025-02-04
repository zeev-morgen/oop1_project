#include "Enemy.h"
#include "Wall.h"
#include "LevelManager.h"
#include <iostream>

std::vector<Enemy*> Enemy::allEnemies;

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position)
	: MoveableObject(texture, position, ENEMY_SPEED), m_startPosition(position)
{
    allEnemies.push_back(this);
    //setOrigin();
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
//void Enemy::update(float deltaTime, LevelManager& levelManager) {
//    sf::Vector2f movement = m_currentDirection * getSpeed() * deltaTime;
//
//    movement.x = std::round(movement.x);
//    movement.y = std::round(movement.y);

    //if (getPosition().x + movement.x < 0 || getPosition().x + movement.x > Config::WINDOW_WIDTH - Config::TILE_WIDTH) {
    //    //m_currentDirection.x *= -1;  // äôéëú ëéååï àåô÷é
    //    changeDirection(deltaTime);
    //}
    //if (getPosition().y + movement.y < 0 || getPosition().y + movement.y > Config::WINDOW_HEIGHT - Config::TILE_WIDTH) {
    //    //m_currentDirection.y *= -1;  // äôéëú ëéååï àðëé
    //    changeDirection(deltaTime);
    //}

  /*  tryMove(movement, levelManager);
}*/


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


void Enemy::collide(Player& other, float deltaTime, LevelManager& levelManager)  {
    //resetLocation();
	/*other.undoMove();
	other.setActive(false);*/
	other.setActive(false);

}

void Enemy::collide(Enemy& other, float deltaTime, LevelManager& levelManager)  {
    // àåéáéí òåáøéí àçã ãøê äùðé
}


void Enemy::collide(Wall& other, float deltaTime, LevelManager& levelManager) {
    changeDirection(deltaTime, levelManager);
}


void Enemy::collide(Rock& other,float deltaTime,LevelManager& levelManager)  {
    changeDirection(deltaTime, levelManager);  // ðú÷ò áàáï
}

void Enemy::collide(Door& other, float deltaTime, LevelManager& levelManager)  {
    undoMove();  // ðú÷ò áãìú
}

void Enemy::collide(Explosion& other, float deltaTime, LevelManager& levelManager)  {
    this->setActive(false);  // ðäøñ îôéöåõ

}

void Enemy::draw(sf::RenderWindow& window) const  {
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

//Enemy::~Enemy() {
//    // äñøú äàåéá îäøùéîä ëùäåà ðäøñ
//    auto it = std::find(allEnemies.begin(), allEnemies.end(), this);
//    if (it != allEnemies.end()) {
//        allEnemies.erase(it);
//    }
//}
