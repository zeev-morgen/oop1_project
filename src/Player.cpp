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
            //levelManager.addBomb(bombPosition); 
            createBomb(bombPosition);
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
	//this->getBombs().clear();
	//להוסיף מחיקת פצצות ופיצוצים אם השחקן נפגע
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

//===============================================
void Player::createBomb(sf::Vector2f position) {
	//load the texture of the bomb and create a new bomb
    TextureManager& textureManager = TextureManager::instance();

    sf::Texture* texture = textureManager.getTexture('%');
    if (!texture) {
        std::cerr << "Failed to get texture for symbol: " << '%' << std::endl;
        return;
    }

    m_bombs.push_back(std::make_unique<Bomb>(*texture, position));
}
//===============================================
std::vector<std::unique_ptr<Bomb>>& Player::getBombs() {
	return m_bombs;
}