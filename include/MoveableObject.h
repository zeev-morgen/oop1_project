#pragma once
#include "GameObject.h"
#include "Config.h"

class LevelManager;

class MoveableObject : public GameObject {
protected:
	float m_speed;
	sf::Vector2f m_direction;
	bool m_isMoving;
	bool isValidPosition(const sf::Vector2f& newPosition, LevelManager& levelManager);
	void tryMove(const sf::Vector2f& movement, LevelManager& levelManager);

public:
	MoveableObject(const sf::Texture& texture, const sf::Vector2f& position, float speed);

	void alignToTile(sf::Vector2f& position);

	virtual void move(const sf::Vector2f& movement);
	virtual void setDirection(sf::Vector2f direction);
	virtual void stop();

	void setSpeed(float speed);
	float getSpeed() const;



	void collide(GameObject& other) override;

	virtual void update(float deltaTime, LevelManager& levelManager) = 0;
};