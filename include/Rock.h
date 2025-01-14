#pragma once
#include "StaticObject.h"

class Rock : public StaticObject {
public:
    Rock(const sf::Texture& texture, const sf::Vector2f& position);

private:
    bool m_isDestroyed = false;
};
