#include "FreezeGift.h"

FreezeGift::FreezeGift(const sf::Texture& texture, const sf::Vector2f& position)
    : Gift(texture, position)
{
}

void FreezeGift::collide(Player& player) {
	//freeze all enemies
    //LevelManager::getInstance().freezeAllEnemies(FREEZE_DURATION);
    setActive(false);
}