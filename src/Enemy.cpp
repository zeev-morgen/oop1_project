#include "Enemy.h"
#include "Wall.h"
#include "LevelManager.h"
#include <iostream>

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, ENEMY_SPEED)
{
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
    //    //m_currentDirection.x *= -1;  // הפיכת כיוון אופקי
    //    changeDirection(deltaTime);
    //}
    //if (getPosition().y + movement.y < 0 || getPosition().y + movement.y > Config::WINDOW_HEIGHT - Config::TILE_WIDTH) {
    //    //m_currentDirection.y *= -1;  // הפיכת כיוון אנכי
    //    changeDirection(deltaTime);
    //}

  /*  tryMove(movement, levelManager);
}*/


//===============================================
void Enemy::changeDirection(float deltaTime, LevelManager& levelManager) {
    const sf::Vector2f possibleDirections[] = {
                {1.0f, 0.0f},   // ימינה
                {-1.0f, 0.0f},  // שמאלה
                {0.0f, 1.0f},   // למטה
                {0.0f, -1.0f}   // למעלה
    };

    // save the current direction
    sf::Vector2f oldDirection = m_currentDirection;
    int attempts = 0;
    do {
        int randomIndex = rand() % 4; // בחר כיוון אקראי מתוך האפשרויות
        m_currentDirection = possibleDirections[randomIndex];
        attempts++;
        // במקרה ואין כיוון תקין לאחר מספר ניסיונות, שמור על הכיוון הקודם
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
    // תקיפת שחקן
}

void Enemy::collide(Enemy& other, float deltaTime, LevelManager& levelManager)  {
    // אויבים עוברים אחד דרך השני
}

void Enemy::collide(Wall& other, float deltaTime, LevelManager& levelManager) {
    // מציאת הקיר הקרוב ביותר לאויב ו הצמדה אליו
    //sf::FloatRect enemyBounds = getBounds();
    //sf::FloatRect wallBounds = other.getBounds();

    //// אם האויב נמצא בצמוד לקיר בציר X
    //if (enemyBounds.left + enemyBounds.width > wallBounds.left && enemyBounds.left < wallBounds.left + wallBounds.width) {
    //    if (enemyBounds.top + enemyBounds.height > wallBounds.top && enemyBounds.top < wallBounds.top + wallBounds.height) {
    //        // הצמד את האויב לקיר בצד המתאים (למשל, אם הוא בא מימין או משמאל)
    //        if (enemyBounds.left < wallBounds.left) {  // אויב מצדו השמאלי של הקיר
    //            setPosition(sf::Vector2f(wallBounds.left - enemyBounds.width, enemyBounds.top));  // העטף את X ו-Y ב- sf::Vector2f
    //        }
    //        else {  // אויב מצדו הימני של הקיר
    //            setPosition(sf::Vector2f(wallBounds.left + wallBounds.width, enemyBounds.top));  // העטף את X ו-Y ב- sf::Vector2f
    //        }
    //    }
    //}
    changeDirection(deltaTime, levelManager);
}


void Enemy::collide(Rock& other,float deltaTime,LevelManager& levelManager)  {
    changeDirection(deltaTime, levelManager);  // נתקע באבן
}

void Enemy::collide(Door& other, float deltaTime, LevelManager& levelManager)  {
    undoMove();  // נתקע בדלת
}

void Enemy::collide(Explosion& other, float deltaTime, LevelManager& levelManager)  {
    //setActive(false);  // נהרס מפיצוץ
}

void Enemy::draw(sf::RenderWindow& window) const  {
    window.draw(m_sprite);
}