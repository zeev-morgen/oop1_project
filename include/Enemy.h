#pragma once
#include "MoveableObject.h"
class LevelManager;


class Enemy : public MoveableObject {
public:
	Enemy(const sf::Texture& texture, const sf::Vector2f& position);
	//void update(float deltaTime);

	virtual void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override;

	virtual void collide(Player& other, float deltaTime, LevelManager& levelManager) override;
	virtual void collide(Enemy& other, float deltaTime, LevelManager& levelManager) override;
	virtual void collide(Wall& other, float deltaTime, LevelManager& levelManager) override;
	virtual void collide(Rock& other, float deltaTime, LevelManager& levelManager) override;
	virtual void collide(Door& other, float deltaTime, LevelManager& levelManager) override;
	virtual void collide(Explosion& other, float deltaTime, LevelManager& levelManager) override;

	void update(float deltaTime, LevelManager& levelManager) override;

	void draw(sf::RenderWindow& window) const override;

private:
	sf::Vector2f m_currentDirection;
	void changeDirection(float deltaTime, LevelManager& levelManager);
	void randomLocation();
	static constexpr float ENEMY_SPEED = 60.0f;

	//bool isExplode();
};

