#include "Gift.h"
#include "LevelManager.h"

class FreezeGift : public Gift {
public:
    FreezeGift(const sf::Texture& texture, const sf::Vector2f& position);
    virtual void collide(Player& player) override;

//private:
//    static const float Config::FREEZE_DURATION; 
};