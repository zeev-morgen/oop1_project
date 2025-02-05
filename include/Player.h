#pragma once
#include "MoveableObject.h"
class LevelManager;

class Player : public MoveableObject {
public:
	Player(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime, LevelManager& levelManager) override;
    bool getFinish();
    virtual void collide(GameObject& other) override;

    virtual void collide(Player& other) override;
    virtual void collide(Enemy& other) override;
    virtual void collide(Wall& other) override;
    virtual void collide(Rock& other) override;
    virtual void collide(Door& other) override;
    virtual void collide(Explosion& other) override;
    //virtual void collide(Gift& other) override;

    void draw(sf::RenderWindow& window) const override;

	void setHealth(int health);
	void setTime(float time);

    //void updateAnimation(float deltaTime);

private:
	float m_moveSpeed;
    bool m_canPlaceBomb = true;
	bool m_isMoving = false;
	int m_lives = 3;
	int m_score = 0;
    int m_time;
	bool m_finishLevel = false;
    

	sf::Vector2f m_startPosition;
    sf::Vector2f m_direction;

    //// הוספת קבועים לאנימציה
    //static constexpr int FRAME_WIDTH = 50;  // רוחב כל פריים באנימציה
    //static constexpr int FRAME_HEIGHT = 50; // גובה כל פריים באנימציה
    //static constexpr int FRAMES_PER_ROW = 3; // כמה פריימים יש בכל שורה

    //// מספרי השורות בספרייט שיט עבור כל כיוון
    //static constexpr int DOWN_ROW = 0;
    //static constexpr int UP_ROW = 1;
    //static constexpr int LEFT_ROW = 2;
    //static constexpr int RIGHT_ROW = 3;

};
