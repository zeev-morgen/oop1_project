#include "Bomb.h"

Bomb::Bomb(const sf::Texture& texture, const sf::Vector2f& position, sf::Font font)
    : StaticObject(texture, position)
{
    m_timer.restart();
    m_font.loadFromFile("ARIAL.TTF");
    m_timerText.setFont(m_font);
    m_timerText.setCharacterSize(24);
    m_timerText.setFillColor(sf::Color::Red);
    m_timerText.setPosition(position.x + Config::TILE_WIDTH / 2, position.y + Config::TILE_WIDTH / 2);
}

//================================================
bool Bomb::hasExploded() const {
    return m_exploded; 
}
//================================================
void Bomb::update(float deltaTime, LevelManager& levelManager) {

    float timeLeft = Config::EXPLOSION_TIME - m_timer.getElapsedTime().asSeconds();
    m_timerText.setString(std::to_string(static_cast<int>(timeLeft))); // הצגת הזמן בשניות
	m_timerText.setOrigin(m_timerText.getLocalBounds().width / 2, m_timerText.getLocalBounds().height / 2);
    // בודקים אם עבר זמן הפיצוץ
    if (m_timer.getElapsedTime().asSeconds() >= Config::EXPLOSION_TIME) {

        if (!m_exploded) {
            levelManager.addExplosion(this->getPosition());
			
            m_exploded = true;
			m_isActive = false;
        }
    }
}
//================================================
bool Bomb::isExploded() const {
    return m_exploded;
}
//================================================
void Bomb::draw(sf::RenderWindow& window) const {
	if (!m_exploded) {
		window.draw(m_sprite);
		window.draw(m_timerText);
	}
}
