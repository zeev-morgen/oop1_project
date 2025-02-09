#pragma once
#include "MoveableObject.h"
#include "Player.h"
#include "SoundManager.h"
class LevelManager;

class Enemy : public MoveableObject {
public:
    Enemy(const sf::Texture& texture, const sf::Vector2f& position);
    //void update(float deltaTime);

    virtual void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override;

    virtual void collide(Player& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Enemy& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Wall& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Rock& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Door& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Explosion& other, float deltaTime, LevelManager& levelManager) override;

    void update(float deltaTime, LevelManager& levelManager) override;

    void draw(sf::RenderWindow& window) const override;
    //~Enemy();
private:
    SoundManager* soundManager; // Use a pointer to the singleton instance
    static std::vector<Enemy*> allEnemies;
    sf::Vector2f m_currentDirection;
    void changeDirection(float deltaTime, LevelManager& levelManager);
    void randomLocation();
    static constexpr float ENEMY_SPEED = 60.0f;

    sf::Vector2f m_startPosition;
    bool isExplode();
    //void PlaySound(SoundManager &sound);
    static void resetLocation();
};
