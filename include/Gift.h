#pragma once
#include "StaticObject.h"
#include "Config.h"

class Gift : public StaticObject {
public:
    Gift(const sf::Texture& texture, const sf::Vector2f& position);

    //virtual void collide(Player& player) override = 0; // pure virtual
    virtual void update(float deltaTime, LevelManager& levelManager) override;
    virtual void draw(sf::RenderWindow& window) const override;

    virtual void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Enemy& enemy, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Wall& wall, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Door& door, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Explosion& explosion, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Player& player, float deltaTime, LevelManager& levelManager) override;

    //void setShow(bool show);

    //virtual void applyEffect(Player& player) = 0;

protected:
    float m_duration = Config::GIFT_DUREATION; // משך הזמן של האפקט (אם רלוונטי)

private:
	//bool m_show;
};