#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	bool m_isActive;

public:
    GameObject(const sf::Texture& texture, const sf::Vector2f& position);
    virtual void update(float deltaTime) {}

    void setOrigin();

    //virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window)const;
    virtual bool checkCollision(const GameObject& other) const;

    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    bool isActive() const;
    sf::Sprite& getSprite();
    const sf::Sprite& getSprite()const;
    virtual ~GameObject() = default;
};