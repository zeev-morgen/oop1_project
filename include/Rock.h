#pragma once
#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"

class Rock : public StaticObject {
public:
    Rock(const sf::Texture& texture, const sf::Vector2f& position);
    void update(float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;
    void collide(Player& player) override;
    void collide(Enemy& enemy) override;
    void collide(Explosion& enemy) override;

private:
    bool m_isDestroyed = false;
};
