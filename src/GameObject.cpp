#include "GameObject.h"
#include "Config.h"

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position)
	: m_sprite(), m_position(position), m_isActive(true), m_prevPosition(position), m_show(false)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
	setToTile(Config::TILE_HEIGHT, Config::TILE_HEIGHT);
}

void GameObject::draw(sf::RenderWindow& window)const {
	if (m_isActive) {
		window.draw(m_sprite);
	}
}

void GameObject::setPosition(const sf::Vector2f& pos) {
	m_position = pos;
	m_sprite.setPosition(pos);
}

bool GameObject::checkCollision(const GameObject& other) const {
	return m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds());
}

bool GameObject::isActive() const{
	return m_isActive;
}

const sf::Vector2f& GameObject::getPosition() const{
	return m_position;
}

void GameObject::setOrigin() {
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

sf::Sprite& GameObject::getSprite() {
	return m_sprite;
}

const sf::Sprite& GameObject::getSprite()const {
	return m_sprite;
}

sf::FloatRect GameObject::getGlobalBounds() const {
	return m_sprite.getGlobalBounds();
}

void GameObject::setToTile(float tileHeight, float tileWidth) {
Object::undoMove() {

void GameObject::undoMove() {
	m_position = m_prevPosition;
	m_sprite.setPosition(m_position);
}

sf::FloatRect GameObject::getBounds() const {
	return m_sprite.getGlobalBounds();
}

void GameObject::setActive(bool active) {
	m_isActive = active;
}

void GameObject::setShow(bool show) {
	m_show = show;
}

bool GameObject::getShow() const {
	return m_show;
}