#pragma once
#include "MoveableObject.h"

class Player : public MoveableObject {
public:
	Player(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime)override;

private:
	float m_moveSpeed;
	sf::Vector2f m_velocity;
};
