#pragma once
#include "MoveableObject.h"
class LevelManager;

class Player : public MoveableObject {
public:
	Player(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime, LevelManager& levelManager) override;



    virtual void collide(GameObject& other) override;

    bool getFinish(); // addition

    virtual void collide(Player& other) override;
    virtual void collide(Enemy& other) override;
    virtual void collide(Wall& other) override;
    virtual void collide(Rock& other) override;
    virtual void collide(Door& other) override;
    virtual void collide(Explosion& other) override;

    void draw(sf::RenderWindow& window) const override;//?
	void setScore(int score);
	int getScore()const;
	void setLives(int lives);
	int getLives()const;
    void setTime(float time);
	void setStatus(bool status);
	bool getStatus() const;


private:
	float m_moveSpeed;
    bool m_canPlaceBomb = true;
	bool m_isMoving = false;
	int m_lives = 3;
	int m_score = 0;
    int m_time;
	bool m_finishLevel = false;
	bool m_status = true;

	sf::Vector2f m_startPosition;
    sf::Vector2f m_direction;
};
