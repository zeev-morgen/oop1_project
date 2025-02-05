#include "Player.h"
#include <iostream>
#include "Config.h"
#include "LevelManager.h"

Player::Player(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, Config::PLAYER_SPEED)
	, m_moveSpeed(Config::PLAYER_SPEED)
    , m_direction(0.0f, 0.0f)
    , m_startPosition(position)
{
    //// אתחול המלבן של האנימציה
    //m_frameRect = sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    //m_sprite.setTextureRect(m_frameRect);
    //m_currentFrame = sf::Vector2i(0, DOWN_ROW);
    //m_animationTimer = 0.0f;
}

void Player::update(float deltaTime, LevelManager& levelManager){
    m_direction = sf::Vector2f(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_direction.x = -1.0f;
		//m_isMoving = true;
        //m_currentFrame.y = LEFT_ROW;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_direction.x = 1.0f;
		//m_isMoving = true;
        //m_currentFrame.y = RIGHT_ROW;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_direction.y = -1.0f;
		//m_isMoving = true;
        //m_currentFrame.y = UP_ROW;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_direction.y = 1.0f;
		//m_isMoving = true;
        //m_currentFrame.y = DOWN_ROW;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (m_canPlaceBomb) {
            sf::Vector2f bombPosition = sf::Vector2f(
                std::round(m_position.x / 50) * 50,
                std::round(m_position.y / 50) * 50
            );
            levelManager.addBomb(bombPosition);  // ֳ₪ֳ¥ֳ±ֳ´ֳ÷ ֳ´ֳ¶ֳ¶ֳ₪
            m_canPlaceBomb = false; // ֳ°ֳ¥ֳ²ֳ¬ ֳ¬ֳ§ֳ©ֳ¶ֳ₪ ֳ§ֳ¥ֳ¦ֳ¸ֳ÷

        }
    }
    else {
        m_canPlaceBomb = true; // ֳ®ֳ¹ֳ§ֳ¸ֳ¸ ֳ ֳ÷ ֳ₪ֳ°ֳ²ֳ©ֳ¬ֳ₪ ֳ«ֳ¹ֳ₪ֳ«ֳ´ֳ÷ֳ¥ֳ¸ ֳ¬ֳ  ֳ¬ֳ§ֳ¥ֳµ
    }
    sf::Vector2f movement = m_direction * m_moveSpeed * deltaTime;

    //set the move to int
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    tryMove(movement, levelManager);

    //updateAnimation(deltaTime);
}


void Player::collide(GameObject& other, float deltaTime, LevelManager& levelManager)  {
    other.collide(*this, deltaTime, levelManager);  // Double dispatch
}

bool Player::getFinish() {
	return m_finishLevel;
}

void Player::collide(Enemy& other, float deltaTime, LevelManager& levelManager)  {

    undoMove();
	m_isActive = false;
	std::cout << "player is :"<< isActive() << std::endl;
}

void Player::collide(Wall& other, float deltaTime, LevelManager& levelManager)  {
    undoMove(); 
    std::cout << "collision" << std::endl;// ֳ°ֳ÷ֳ·ֳ² ֳ¡ֳ·ֳ©ֳ¸
}

void Player::collide(Rock& other float deltaTime, LevelManager& levelManager) {
    undoMove(); 
}

void Player::collide(Door& other, float deltaTime, LevelManager& levelManager)  {
    undoMove();
	m_finishLevel = true;
}

void Player::collide(Explosion& other, float deltaTime, LevelManager& levelManager)  {
	undoMove();
    setActive(false);
	std::cout << "collision" << std::endl;
	//m_position = m_startPosition;
}

void Player::collide(Player& other, float deltaTime, LevelManager& levelManager) {
	//not implemented can not exist

}

//void Player::collide(Gift& other) {
//	other.setActive(false);
//}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Player::setHealth(int health) {
	m_lives = health;
}

void Player::setTime(float time) {
	m_time = time;
}


//void Player::updateAnimation(float deltaTime) {
//    m_animationTimer += deltaTime;
//
//    // עדכון האנימציה רק אם השחקן זז
//    if (m_direction.x != 0 || m_direction.y != 0) {
//        if (m_animationTimer >= ANIMATION_SPEED) {
//            m_animationTimer = 0;
//
//            // התקדמות לפריים הבא
//            m_currentFrame.x = (m_currentFrame.x + 1) % FRAMES_PER_ROW;
//
//            // עדכון המלבן שמציג את הפריים הנוכחי
//            m_frameRect.left = m_currentFrame.x * FRAME_WIDTH;
//            m_frameRect.top = m_currentFrame.y * FRAME_HEIGHT;
//            m_sprite.setTextureRect(m_frameRect);
//        }
//    }
//    else {
//        // כשהשחקן לא זז, מציגים את הפריים הראשון
//        m_currentFrame.x = 0;
//        m_frameRect.left = 0;
//        m_sprite.setTextureRect(m_frameRect);
//    }
//}



void Player::setScore(int score) {
	playerScore = score;
}

int Player::getScore() const{
    return playerScore;
}

void Player::setLives(int lives) {
	playerLives = lives;
}

int Player::getLives() const{
	return playerLives;
}

