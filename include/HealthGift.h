#include "Gift.h"
#include "Player.h"

class HealthGift : public Gift {
public:
    HealthGift(const sf::Texture& texture, const sf::Vector2f& position);
    virtual void collide(Player& player) override;

private:
    static const int HEALTH_BONUS = 1;
};