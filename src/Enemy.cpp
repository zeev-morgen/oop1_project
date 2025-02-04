#include "Enemy.h"
#include "Wall.h"
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

    //if (getPosition().x + movement.x < 0 || getPosition().x + movement.x > Config::WINDOW_WIDTH - Config::TILE_WIDTH) {
    //    //m_currentDirection.x *= -1;  // הפיכת כיוון אופקי
    //    changeDirection(deltaTime);
    //}
    //if (getPosition().y + movement.y < 0 || getPosition().y + movement.y > Config::WINDOW_HEIGHT - Config::TILE_WIDTH) {
    //    //m_currentDirection.y *= -1;  // הפיכת כיוון אנכי
    //    changeDirection(deltaTime);
    //}

    tryMove(movement, levelManager);
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
 /*   do {
        int randomIndex = rand() % 4;
        m_currentDirection = possibleDirections[randomIndex];
    } */
//while (!isValidPosition(getPosition() + (m_currentDirection * getSpeed() * deltaTime)));
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
}

void Enemy::collide(Enemy& other)  {
    // אויבים עוברים אחד דרך השני
}

void Enemy::collide(Wall& other) {
	undoMove();
}


void Enemy::collide(Rock& other)  {
    undoMove();  // נתקע באבן
}

void Enemy::collide(Door& other)  {
    undoMove();  // נתקע בדלת
}

void Enemy::collide(Explosion& other)  {
    this->setActive(false);  // נהרס מפיצוץ
}

void Enemy::draw(sf::RenderWindow& window) const  {
    window.draw(m_sprite);
}

//פונקצייה להחזרת שומרים למיקום התחלתי
void Enemy::resetLocation() {
    for (Enemy* enemy : allEnemies) {
        if (enemy->isActive()) {
            enemy->setPosition(enemy->m_startPosition);
        }
    }
}

//Enemy::~Enemy() {
//    // הסרת האויב מהרשימה כשהוא נהרס
//    auto it = std::find(allEnemies.begin(), allEnemies.end(), this);
//    if (it != allEnemies.end()) {
//        allEnemies.erase(it);
//    }
//}
