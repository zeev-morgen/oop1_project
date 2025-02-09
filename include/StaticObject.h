#pragma once
#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject(const sf::Texture& texture, const sf::Vector2f& position);

	//virtual void update(float deltaTime) override {}
	bool isDestructible() const;

	//void collide(GameObject& other) override;

	//virtual void collide(GameObject& other) override;
	/*virtual void collide(Player& player) override {}
	virtual void collide(Enemy& enemy) override {}
	virtual void collide(Wall& wall) override {}
	virtual void collide(Rock& rock) override {}
	virtual void collide(Door& door) override {}
	virtual void collide(Explosion& explosion) override {}
	virtual void collide(SmartEnemy& smartEnemy)override {}*/


	virtual void update(float deltaTime, LevelManager& levelManager) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;


protected:
	bool m_isCollidable;
};