#pragma once
#include "MoveableObject.h"

class Enemy : public MoveableObject {
public:
	Enemy(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime);

private:
	sf::Vector2f m_currentDirection;
	void changeDirection(float deltaTime);
	void randomLocation();
	static constexpr float ENEMY_SPEED = 60.0f;

	bool isExplode();
};

