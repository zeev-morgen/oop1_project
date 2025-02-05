#pragma once
#include "Door.h"
#include "StaticObject.h"
#include "Player.h"

class Door : public StaticObject {
public:
    Door(const sf::Texture& texture, const sf::Vector2f& position);
    void update(float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;


    void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override;
    void collide(Enemy& other, float deltaTime, LevelManager& levelManager) override;
    void collide(Player& other, float deltaTime, LevelManager& levelManager)override;
    void collide(Explosion& other, float deltaTime, LevelManager& levelManager)override;
};

