#pragma once
#include "StaticObject.h"
#include "Config.h"
#include <iostream>
#include "LevelManager.h"

class Bomb : public StaticObject {
public:
    Bomb(const sf::Texture& texture, const sf::Vector2f& position, sf::Font font);
    bool hasExploded() const;
    void update(float deltaTime, LevelManager& levelManager);
    void explode();
    bool isExploded() const;
    void draw(sf::RenderWindow& window) const override;


private:
    sf::Vector2f m_position;
    float m_explodeTime = Config::EXPLOSION_TIME;
    sf::Clock m_timer;
    bool m_exploded = false;
    sf::Text m_timerText;
    sf::Font m_font;
};
