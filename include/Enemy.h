#pragma once
#include "MoveableObject.h"
#include "Player.h"
class LevelManager;





class Enemy : public MoveableObject {
public:
	Enemy(const sf::Texture& texture, const sf::Vector2f& position);
	//void update(float deltaTime);

	virtual void collide(GameObject& other) override;

	virtual void collide(Player& other) override;
	virtual void collide(Enemy& other) override;
	virtual void collide(Wall& other) override;
	virtual void collide(Rock& other) override;
	virtual void collide(Door& other) override;
	virtual void collide(Explosion& other) override;
	virtual void collide(SmartEnemy& other) override;

	void update(float deltaTime, LevelManager& levelManager) override;

	void draw(sf::RenderWindow& window) const override;
	void randomLocation();
	void freeze(float duration);
	
	//~Enemy();
private:
	static std::vector<Enemy*> allEnemies;
	sf::Vector2f m_currentDirection;
	
	
	static constexpr float ENEMY_SPEED = 60.0f;

	sf::Vector2f m_startPosition;
	bool isExplode();
	static void resetLocation();
};

