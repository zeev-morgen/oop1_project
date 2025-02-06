#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "StaticObject.h"
#include "LevelManager.h"

class Explosion : public StaticObject {
public:
    Explosion(const sf::Texture& texture, const sf::Vector2f& position, sf::Font font);
    void update(float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;

    void collide(GameObject& other) override;
    void collide(Enemy& other) override;
    void collide(Player& other)override;
    void collide(Explosion& other)override;
    void collide(Rock& other)override;


private:
    sf::Clock m_lifetimeClock;
    float m_lifetime = Config::EXP_LIFE_TIME; 
};
