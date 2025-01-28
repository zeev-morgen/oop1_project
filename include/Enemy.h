#pragma once
#include "MoveableObject.h"

class Enemy : public MoveableObject {
public:
	Enemy(const sf::Texture& texture, const sf::Vector2f& position);
	//void update(float deltaTime);

	virtual void collide(GameObject& other) override;

	virtual void collide(Player& other) override;
	virtual void collide(Enemy& other) override;
	virtual void collide(Wall& other) override;
	virtual void collide(Rock& other) override;
	virtual void collide(Door& other) override;
	virtual void collide(Explosion& other) override;

	void update(float deltaTime, LevelManager& levelManager) override;

private:
	sf::Vector2f m_currentDirection;
	void changeDirection(float deltaTime);
	void randomLocation();
	static constexpr float ENEMY_SPEED = 60.0f;

	bool isExplode();
};

