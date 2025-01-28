#pragma once
#include "StaticObject.h"

class Wall : public StaticObject {
public:
    Wall(const sf::Texture& texture, const sf::Vector2f& position);

    void collide(GameObject& other) override;
    void collide(Player& player) override;
    void collide(Enemy& enemy) override;
    //void collide(Wall& wall) override;
    //void collide(Door& door) override;
    void collide(Explosion& explosion) override;
};

