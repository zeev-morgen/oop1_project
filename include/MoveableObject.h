#pragma once
#include "GameObject.h"

class MoveableObject : public GameObject {
protected:
	float m_speed;
	sf::Vector2f m_direction;
	bool m_isMoving;

public:
	MoveableObject(const sf::Texture& texture,
		const sf::Vector2f& position,
		float speed);

	virtual void move(float deltaTime);
	virtual void setDirection(sf::Vector2f direction);
	virtual bool isValidPosition(const sf::Vector2f& pos) const;
	virtual void stop();

	void setSpeed(float speed);
	float getSpeed() const;
};