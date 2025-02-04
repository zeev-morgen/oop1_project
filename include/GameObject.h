#pragma once
#include <SFML/Graphics.hpp>
//#include "LevelManager.h"

class Player;
class Enemy;
class Wall;
class Rock;
class Door;
class Explosion;
class LevelManager;

class GameObject {
protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
    sf::Vector2f m_prevPosition;
	bool m_isActive;

public:
    GameObject(const sf::Texture& texture, const sf::Vector2f& position);
    //virtual void update(float deltaTime) {}

    //LevelManager m_levelManager;

    void setOrigin();
    void setToTile(float tileHeight, float tileWidth);

    //virtual void draw(sf::RenderWindow& window)const;
    virtual bool checkCollision(const GameObject& other) const;
    sf::FloatRect getGlobalBounds()const;
    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    bool isActive() const;
    sf::Sprite& getSprite();
    const sf::Sprite& getSprite()const;
    virtual ~GameObject() = default;
    sf::FloatRect getBounds() const;

    virtual void collide(GameObject& other, float deltaTime, LevelManager& levelManager) = 0;

    virtual void collide(Player& other, float deltaTime, LevelManager& levelManager) = 0;
    virtual void collide(Enemy& other,float deltaTime, LevelManager& levelManager) = 0;
    virtual void collide(Wall& other, float deltaTime, LevelManager& levelManager) = 0;
    virtual void collide(Rock& other, float deltaTime, LevelManager& levelManager) = 0;
    virtual void collide(Door& other, float deltaTime, LevelManager& levelManager) = 0;
    virtual void collide(Explosion& other, float deltaTime, LevelManager& levelManager) = 0;

    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual void update(float deltaTime, LevelManager& levelManager) = 0;
    //virtual void drawSpecific(sf::RenderWindow& window) const = 0;

    void undoMove();
};