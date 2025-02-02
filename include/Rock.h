#pragma once
#include "StaticObject.h"

class Rock : public StaticObject {
public:
    Rock(const sf::Texture& texture, const sf::Vector2f& position);
    void update(float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;

private:
    bool m_isDestroyed = false;
};
