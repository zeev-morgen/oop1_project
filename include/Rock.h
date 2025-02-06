#pragma once
#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Gift.h"

class Rock : public StaticObject {
public:
    Rock(const sf::Texture& texture, const sf::Vector2f& position);

    void update(float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;

    void collide(Player& player) override;
    void collide(Enemy& enemy) override;
    void collide(Explosion& enemy) override;
    void setGift(std::unique_ptr<Gift> gift);
    void setGiftIndex(size_t index);
    size_t getGiftIndex() const;
	bool getHasGift() const;

private:
    //std::unique_ptr<Gift> m_gift;
    bool m_hasGift;
	size_t m_giftIndex;
    std::unique_ptr<Gift> m_gift;
};
