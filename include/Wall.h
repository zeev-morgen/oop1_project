#pragma once
#include "StaticObject.h"

class Wall : public StaticObject {
public:
    Wall(const sf::Texture& texture, const sf::Vector2f& position);
};

