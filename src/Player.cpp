#include "Player.h"
#include <iostream>
#include "Config.h"

Player::Player(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, Config::PLAYER_SPEED)
    , m_moveSpeed(Config::PLAYER_SPEED), m_velocity(0.0f, 0.0f)
{
    setOrigin();
}

void Player::update(float deltaTime){
    // קבלת קלט מהמקלדת
    m_velocity = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_velocity.x = -1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_velocity.x = 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_velocity.y = -1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_velocity.y = 1.0f;


    // חישוב התנועה לפי הזמן שעבר
    sf::Vector2f movement = m_velocity * m_moveSpeed * deltaTime;
    move(movement);
}
