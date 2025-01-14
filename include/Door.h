#pragma once
#include "Door.h"
#include "StaticObject.h"

class Door : public StaticObject {
public:
    Door(const sf::Texture& texture, const sf::Vector2f& position);
};