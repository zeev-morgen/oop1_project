#pragma once
#include "GameObject.h"
#include "Config.h"


class LevelManager;

class MoveableObject : public GameObject {
protected:
	float m_speed;
	sf::Vector2f m_direction;
	sf::Vector2f m_currentDirection;
	float m_freezeTime;
	bool m_isMoving;
	bool m_isFrozen;
	float m_freezeTimeLeft;
	bool isValidPosition(const sf::Vector2f& newPosition, LevelManager& levelManager);
	void tryMove(const sf::Vector2f& movement, LevelManager& levelManager);
	void alignToTile();
	bool m_isBlocked = false;
	bool canMoveInDirection(const sf::Vector2f& direction, float speed, float deltaTime, LevelManager& levelManager) {
		sf::Vector2f testMove = direction * speed * deltaTime;
		return isValidPosition(getPosition() + testMove, levelManager);
	}
	void changeDirection();

public:
	MoveableObject(const sf::Texture& texture, const sf::Vector2f& position, float speed);

	virtual void move(const sf::Vector2f& movement);
	virtual void setDirection(sf::Vector2f direction);
	virtual void stop();

	void setSpeed(float speed);
	float getSpeed() const;


	bool isBlocked() const;

	virtual void update(float deltaTime, LevelManager& levelManager) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;

};