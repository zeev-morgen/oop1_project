#include "Player.h"
#include <iostream>

Player::Player(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, PLAYER_SPEED)
{
    setOrigin();
}

void Player::handleInput() {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction.x = -1.f;
        std::cout << "Moving Left\n"; // הדפסת דיבאג
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction.x = 1.f;
        std::cout << "Moving Right\n";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction.y = -1.f;
        std::cout << "Moving Up\n";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction.y = 1.f;
        std::cout << "Moving Down\n";
    }

    setDirection(direction);
}

void Player::update(float deltaTime) {
    handleInput();
    move(deltaTime);
}