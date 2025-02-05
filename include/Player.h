#pragma once
#include "MoveableObject.h"
class LevelManager;

class Player : public MoveableObject {
public:
	Player(const sf::Texture& texture, const sf::Vector2f& position);
	void update(float deltaTime, LevelManager& levelManager) override;



    virtual void collide(GameObject& other, float deltaTime, LevelManager& levelManager) override;

    bool getFinish(); // addition



	
    //void updateAnimation(float deltaTime);

    virtual void collide(Player& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Enemy& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Wall& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Rock& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Door& other, float deltaTime, LevelManager& levelManager) override;
    virtual void collide(Explosion& other, float deltaTime, LevelManager& levelManager) override;

    void draw(sf::RenderWindow& window) const override;//?
	void setScore(int score);
	int getScore()const;
	void setLives(int lives);
	int getLives()const;
  void setTime(float time);


private:
	float m_moveSpeed;
  
	sf::Vector2f m_direction; // addition
    int playerLives = 3;  // addition
    int playerScore = 0; // addition

    bool m_canPlaceBomb = true;
	bool m_isMoving = false;
	int m_lives = 3;
	int m_score = 0;
    int m_time;
	bool m_finishLevel = false;
    

	sf::Vector2f m_startPosition;
    sf::Vector2f m_direction;

    //// ����� ������ ��������
    //static constexpr int FRAME_WIDTH = 50;  // ���� �� ����� ��������
    //static constexpr int FRAME_HEIGHT = 50; // ���� �� ����� ��������
    //static constexpr int FRAMES_PER_ROW = 3; // ��� ������� �� ��� ����

    //// ����� ������ ������� ��� ���� �� �����
    //static constexpr int DOWN_ROW = 0;
    //static constexpr int UP_ROW = 1;
    //static constexpr int LEFT_ROW = 2;
    //static constexpr int RIGHT_ROW = 3;

};
