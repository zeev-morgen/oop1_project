#pragma once
#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject(const sf::Texture& texture, const sf::Vector2f& position);

	virtual void update(float deltaTime) override {}
	bool isDestructible() const;

protected:
	bool m_isCollidable;
};