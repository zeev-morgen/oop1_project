#pragma once
#include "StaticObject.h"

class Wall : public StaticObject {
public:
    Wall(const sf::Texture& texture, const sf::Vector2f& position);

    void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override;
    void collide(Player& player, float deltaTime, LevelManager& levelManager) override;
    void collide(Enemy& enemy, float deltaTime, LevelManager& levelManager) override;
    //void collide(Wall& wall) override;
    //void collide(Door& door) override;
    void collide(Explosion& explosion, float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;

    void update(float deltaTime, LevelManager& levelManager) override;
};

