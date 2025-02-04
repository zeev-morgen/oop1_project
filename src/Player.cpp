#include "Player.h"
#include <iostream>
#include "Config.h"
#include "LevelManager.h"

Player::Player(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, Config::PLAYER_SPEED)
	, m_moveSpeed(Config::PLAYER_SPEED), m_direction(0.0f, 0.0f), m_startPosition(position)
{
    //setOrigin();
}

void Player::update(float deltaTime, LevelManager& levelManager){

    m_direction = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_direction.x = -1.0f;
		//m_isMoving = true;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_direction.x = 1.0f;
		//m_isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_direction.y = -1.0f;
		//m_isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_direction.y = 1.0f;
		//m_isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (m_canPlaceBomb) {
            sf::Vector2f bombPosition = sf::Vector2f(
                std::round(m_position.x / 50) * 50,
                std::round(m_position.y / 50) * 50
            );
            levelManager.addBomb(bombPosition);  // äåñôú ôööä
            m_canPlaceBomb = false; // ðåòì ìçéöä çåæøú

        }
    }
    else {
        m_canPlaceBomb = true; // îùçøø àú äðòéìä ëùäëôúåø ìà ìçåõ
    }
    sf::Vector2f movement = m_direction * m_moveSpeed * deltaTime;

    //set the move to int
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    tryMove(movement, levelManager);
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
    std::cout << "collision" << std::endl;// ðú÷ò á÷éø
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

void Player::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}


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

