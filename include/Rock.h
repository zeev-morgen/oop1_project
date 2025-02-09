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

    void setGift(std::unique_ptr<Gift> gift);
    void setGiftIndex(size_t index);
    size_t getGiftIndex() const;
	bool getHasGift() const;

    virtual void collide(GameObject& other) override;

    virtual void collide(Player& player) override;
    virtual void collide(Enemy& enemy) override;
    virtual void collide(Wall& wall) override;
    virtual void collide(Rock& rock) override;
    virtual void collide(Door& door) override;
    virtual void collide(Explosion& explosion) override;
    virtual void collide(SmartEnemy& smartEnemy)override;

private:
    //std::unique_ptr<Gift> m_gift;
    bool m_hasGift;
	size_t m_giftIndex;
    std::unique_ptr<Gift> m_gift;
};
