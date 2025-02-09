#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Bomb.h"

class SmartEnemy : public MoveableObject {
public:
    SmartEnemy(const sf::Texture& texture, const sf::Vector2f& position);

    void collide(GameObject& other) override;
    void collide(Player& other) override;
    void collide(Enemy& other) override;
    void collide(Wall& other) override;
    void collide(Rock& other) override;
    void collide(Door& other) override;
    void collide(Explosion& other) override;
    void collide(SmartEnemy& smartEnemy)override;
    

    void update(float deltaTime, LevelManager& levelManager) override;
    void draw(sf::RenderWindow& window) const override;


private:
    void chasePlayer(const Player& player);
    void avoidBombs(const std::vector<std::unique_ptr<GameObject>>& gameObjects);
    bool isNearBomb(const sf::Vector2f& position, const std::vector<std::unique_ptr<GameObject>>& gameObjects);
	sf::Vector2f m_currentDirection;
	void move(float deltaTime, LevelManager& levelManager);

};