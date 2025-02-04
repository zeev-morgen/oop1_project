#pragma once
#include "MoveableObject.h"
class LevelManager;

class Player : public MoveableObject {
public:
	Player(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime, LevelManager& levelManager) override;

    virtual void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override;

    virtual void collide(Player& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Enemy& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Wall& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Rock& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Door& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Explosion& other, float deltaTime, LevelManager& levelManager) override;

    void draw(sf::RenderWindow& window) const override;
	void setScore(int score);
	int getScore()const;
	void setLives(int lives);
	int getLives()const;

private:
	float m_moveSpeed;
	sf::Vector2f m_direction;
    int playerLives = 3; 
    int playerScore = 0;
    bool m_canPlaceBomb = true;
	bool m_isMoving = false;
};
