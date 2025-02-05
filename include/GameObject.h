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
	bool m_show;

    sf::Vector2i m_currentFrame;     // מיקום הפריים הנוכחי
    sf::IntRect m_frameRect;         // מלבן שמגדיר את החלק הנוכחי מהטקסטורה
    float m_animationTimer;          // טיימר לאנימציה
    static constexpr float ANIMATION_SPEED = 0.1f; // מהירות האנימציה

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
	void setActive(bool active);
	void setShow(bool show);
	bool getShow() const;

    virtual void collide(GameObject& other) = 0;

    virtual void collide(Player& other) = 0;
    virtual void collide(Enemy& other) = 0;
    virtual void collide(Wall& other) = 0;
    virtual void collide(Rock& other) = 0;
    virtual void collide(Door& other) = 0;
    virtual void collide(Explosion& other) = 0;

    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual void update(float deltaTime, LevelManager& levelManager) = 0;
    //virtual void drawSpecific(sf::RenderWindow& window) const = 0;

    void undoMove();
};