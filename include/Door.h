#pragma once
#include "Door.h"
#include "StaticObject.h"
#include "Player.h"

class Door : public StaticObject {
public:
    Door(const sf::Texture& texture, const sf::Vector2f& position);
    void update(float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;


    void collide(GameObject& other) override;

    void collide(Enemy& other) override;
    void collide(Player& other)override;
    void collide(Explosion& other)override;
	void collide(Rock& other)override;
	void collide(Wall& other) override;
	void collide(Door& other) override;
	void collide(SmartEnemy& other)override;
};

