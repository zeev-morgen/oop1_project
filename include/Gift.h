#pragma once
#include "StaticObject.h"
#include "Config.h"

class Gift : public StaticObject {
public:
    Gift(const sf::Texture& texture, const sf::Vector2f& position);

    //virtual void collide(Player& player) override = 0; // pure virtual
    virtual void update(float deltaTime, LevelManager& levelManager) override;
    virtual void draw(sf::RenderWindow& window) const override;

    virtual void collide(GameObject& other) override;
    virtual void collide(Enemy& enemy) override;
    virtual void collide(Wall& wall) override;
    virtual void collide(Rock& rock) override;
    virtual void collide(Door& door) override;
    virtual void collide(Explosion& explosion) override;
    virtual void collide(Player& player) override;

    //void setShow(bool show);

    //virtual void applyEffect(Player& player) = 0;

protected:
    float m_duration = Config::GIFT_DUREATION; // משך הזמן של האפקט (אם רלוונטי)

private:
	//bool m_show;
};