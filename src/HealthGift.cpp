#include "HealthGift.h"

HealthGift::HealthGift(const sf::Texture& texture, const sf::Vector2f& position)
    : Gift(texture, position)
{
}

void HealthGift::collide(Player& player) {
    player.setLives(HEALTH_BONUS);
    setActive(false); // המתנה נעלמת אחרי השימוש
}