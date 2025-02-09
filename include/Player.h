#pragma once
#include "MoveableObject.h"
#include "Bomb.h"
#include <memory>
class LevelManager;
class Bomb;
class SmartEnemy;

class Player : public MoveableObject {
public:
	Player(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime, LevelManager& levelManager) override;



    virtual void collide(GameObject& other) override;

    bool getFinish()const; // addition

    virtual void collide(Player& other) override;
    virtual void collide(Enemy& other) override;
    virtual void collide(Wall& other) override;
    virtual void collide(Rock& other) override;
    virtual void collide(Door& other) override;
    virtual void collide(Explosion& other) override;
	virtual void collide(SmartEnemy& other)override;

    void draw(sf::RenderWindow& window) const override;//?
	void setScore(int score);
	int getScore()const;
	void setLives(int lives);
	int getLives()const;
    void setTime(float time);
	void setStatus(bool status);
	bool getStatus() const;
	std::vector<std::unique_ptr<Bomb>>& getBombs();

private:
	float m_moveSpeed;
    bool m_canPlaceBomb = true;
	bool m_isMoving = false;
	int m_lives = 3;
	int m_score = 0;
    float m_time;
	bool m_finishLevel = false;
	bool m_status = true;
	void createBomb(sf::Vector2f pos);
	std::vector<std::unique_ptr<Bomb>> m_bombs;

    
	sf::Vector2f m_startPosition;
    sf::Vector2f m_direction;
};
