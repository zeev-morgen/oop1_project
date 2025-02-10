#include "HealthGift.h"

HealthGift::HealthGift(const sf::Texture& texture, const sf::Vector2f& position)
    : Gift(texture, position)
{
}

void HealthGift::collide(Player& player) {
    player.setLives(player.getLives() + 1);
    setActive(false); 
}