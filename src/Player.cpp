#include "Player.h"
#include <iostream>
#include "Config.h"
#include "LevelManager.h"

Player::Player(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, Config::PLAYER_SPEED)
	, m_moveSpeed(Config::PLAYER_SPEED)
    , m_direction(0.0f, 0.0f)
    , m_startPosition(position)
    , m_time(Config::GAME_TIME)
{
}

void Player::update(float deltaTime, LevelManager& levelManager){
    m_direction = sf::Vector2f(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_direction.x = -1.0f;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_direction.x = 1.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_direction.y = -1.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_direction.y = 1.0f;
    }

    sf::Vector2f movement = m_direction * m_moveSpeed * deltaTime;

    // במקום עיגול למספרים שלמים, נשתמש בהחלקה עדינה יותר
    sf::Vector2f targetPos = m_position + movement;

    if (m_direction.x != 0) {  // תנועה אופקית
        float targetY = std::round(m_position.y / 50) * 50;
        float diff = targetY - m_position.y;
        if (std::abs(diff) < m_moveSpeed * deltaTime) {
            movement.y = diff;
        }
    }
    else if (m_direction.y != 0) {  // תנועה אנכית
        float targetX = std::round(m_position.x / 50) * 50;
        float diff = targetX - m_position.x;
        if (std::abs(diff) < m_moveSpeed * deltaTime) {
            movement.x = diff;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (m_canPlaceBomb) {
            sf::Vector2f bombPosition = sf::Vector2f(
                std::round(m_position.x / 50) * 50,
                std::round(m_position.y / 50) * 50
            );
            levelManager.addBomb(bombPosition);  
            m_canPlaceBomb = false; 

        }
    }
    else {
        m_canPlaceBomb = true; 
    }
    //sf::Vector2f movement = m_direction * m_moveSpeed * deltaTime;

    //set the move to int
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    tryMove(movement, levelManager);
}


void Player::collide(GameObject& other)  {
    other.collide(*this);
}

bool Player::getFinish() const{
	return m_finishLevel;
}

void Player::collide(Enemy& other)  {

    undoMove();
	m_status = false;
	m_lives--;
	std::cout << "player is :"<< isActive() << std::endl;
}

void Player::collide(Wall& other)  {
    undoMove(); 
    std::cout << "collision" << std::endl;
}

void Player::collide(Rock& other) {
    undoMove(); 
}

void Player::collide(Door& other)  {
    undoMove();
	m_finishLevel = true;
}

void Player::collide(Explosion& other)  {
	undoMove();
    setStatus(false);
	this->m_lives--;
	std::cout << "collision" << std::endl;
}

void Player::collide(Player& other) {

}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Player::setLives(int health) {
	m_lives = health;
}

void Player::setTime(float time) {
	m_time = time;
}

void Player::setScore(int score) {
    m_score = score;
}

int Player::getScore() const {
    return m_score;
}

int Player::getLives() const {
    return m_lives;
}

void Player::setStatus(bool status) {
	m_status = status;
}

bool Player::getStatus() const {
	return m_status;
}

//void Player::update(float deltaTime, LevelManager& levelManager) {
//    m_direction = sf::Vector2f(0.0f, 0.0f);
//
//    // בדיקה איזה מקשים לחוצים כרגע
//    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
//    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
//    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
//    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
//
//    // שמירת הכיוון הקודם לפני העדכון
//    sf::Vector2f previousDirection = m_direction;
//    Direction previousLastDirection = m_lastDirection;
//
//    // קביעת הכיוון בהתבסס על המקש האחרון שנלחץ
//    if (leftPressed && !rightPressed) {
//        m_direction.x = -1.0f;
//        m_lastDirection = Direction::Left;
//    }
//    else if (rightPressed && !leftPressed) {
//        m_direction.x = 1.0f;
//        m_lastDirection = Direction::Right;
//    }
//    else if (upPressed && !downPressed) {
//        m_direction.y = -1.0f;
//        m_lastDirection = Direction::Up;
//    }
//    else if (downPressed && !upPressed) {
//        m_direction.y = 1.0f;
//        m_lastDirection = Direction::Down;
//    }
//
//    // חישוב התנועה הראשונית
//    sf::Vector2f movement = m_direction * m_moveSpeed * deltaTime;
//
//    const float GRID_SIZE = 50.0f;
//    const float SNAP_THRESHOLD = 15.0f;
//    const float CORNER_THRESHOLD = GRID_SIZE * 0.7f; // סף לבדיקת מעבר פינה
//
//    // שמירת המיקום הנוכחי לפני הניסיון לזוז
//    sf::Vector2f originalPos = m_position;
//
//    // ניסיון ראשון לזוז
//    tryMove(movement, levelManager);
//
//    // אם התנועה נחסמה (המיקום לא השתנה) ויש כיוון תנועה
//    if (m_position == originalPos && m_direction != sf::Vector2f(0.0f, 0.0f)) {
//        // בדיקה אם אנחנו קרובים לפינה של משבצת
//        sf::Vector2f currentCell(
//            std::round(m_position.x / GRID_SIZE) * GRID_SIZE,
//            std::round(m_position.y / GRID_SIZE) * GRID_SIZE
//        );
//
//        float xOffset = std::abs(m_position.x - currentCell.x);
//        float yOffset = std::abs(m_position.y - currentCell.y);
//
//        // ניסיון להחליק לצד המתאים
//        sf::Vector2f slideMovement(0.0f, 0.0f);
//
//        if (m_direction.x != 0) { // אם מנסים לנוע שמאלה או ימינה
//            // בודק אם קרוב יותר לתא העליון או התחתון
//            if (yOffset > 0) {
//                if (m_position.y > currentCell.y) {
//                    slideMovement.y = 1.0f; // החלקה למטה
//                }
//                else {
//                    slideMovement.y = -1.0f; // החלקה למעלה
//                }
//            }
//        }
//        else if (m_direction.y != 0) { // אם מנסים לנוע למעלה או למטה
//            // בודק אם קרוב יותר לתא השמאלי או הימני
//            if (xOffset > 0) {
//                if (m_position.x > currentCell.x) {
//                    slideMovement.x = 1.0f; // החלקה ימינה
//                }
//                else {
//                    slideMovement.x = -1.0f; // החלקה שמאלה
//                }
//            }
//        }
//
//        // אם מצאנו כיוון החלקה, מנסים להחליק
//        if (slideMovement != sf::Vector2f(0.0f, 0.0f)) {
//            sf::Vector2f slideAttempt = slideMovement * m_moveSpeed * deltaTime;
//            tryMove(slideAttempt, levelManager);
//
//            // אם ההחלקה הצליחה, מנסים שוב את התנועה המקורית
//            if (m_position != originalPos) {
//                tryMove(movement, levelManager);
//            }
//        }
//    }
//
//    // טיפול בהנחת פצצות
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//        if (m_canPlaceBomb) {
//            sf::Vector2f bombPosition = sf::Vector2f(
//                std::round(m_position.x / GRID_SIZE) * GRID_SIZE,
//                std::round(m_position.y / GRID_SIZE) * GRID_SIZE
//            );
//            levelManager.addBomb(bombPosition);
//            m_canPlaceBomb = false;
//        }
//    }
//    else {
//        m_canPlaceBomb = true;
//    }
//}