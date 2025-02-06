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
    sf::Vector2f movement = m_direction * m_moveSpeed * deltaTime;

    //set the move to int
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    tryMove(movement, levelManager);
}


void Player::collide(GameObject& other)  {
    other.collide(*this);
}

bool Player::getFinish() {
	return m_finishLevel;
}

void Player::collide(Enemy& other)  {

    undoMove();
	m_isActive = false;
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
    setActive(false);
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