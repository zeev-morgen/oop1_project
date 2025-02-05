#include "Gift.h"
#include "Player.h"

class TimeGift : public Gift {
public:
    TimeGift(const sf::Texture& texture, const sf::Vector2f& position);
    virtual void collide(Player& player, float deltaTime, LevelManager& levelManager) override;
private:
    static const float TIME_BONUS; // 30 seconds
};