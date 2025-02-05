#pragma once
#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject(const sf::Texture& texture, const sf::Vector2f& position);

	//virtual void update(float deltaTime) override {}
	bool isDestructible() const;

	//void collide(GameObject& other) override;

	virtual void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override {}
	virtual void collide(Player& player, float deltaTime, LevelManager& levelManager) override {}
	virtual void collide(Enemy& enemy, float deltaTime, LevelManager& levelManager) override {}
	virtual void collide(Wall& wall, float deltaTime, LevelManager& levelManager) override {}
	virtual void collide(Rock& rock, float deltaTime, LevelManager& levelManager) override {}
	virtual void collide(Door& door, float deltaTime, LevelManager& levelManager) override {}
	virtual void collide(Explosion& explosion, float deltaTime, LevelManager& levelManager) override {}

	virtual void update(float deltaTime, LevelManager& levelManager) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;


protected:
	bool m_isCollidable;
};