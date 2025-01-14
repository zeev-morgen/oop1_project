#pragma once
#include "MoveableObject.h"

class Player : public MoveableObject {
public:
	Player(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime);
	void handleInput();

private:
	static constexpr float PLAYER_SPEED = 200.0f;
};
