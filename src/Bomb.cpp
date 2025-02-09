#include "Bomb.h"

Bomb::Bomb(const sf::Texture& texture, const sf::Vector2f& position)
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
    m_timerText.setString(std::to_string(static_cast<int>(timeLeft))); 
	m_timerText.setOrigin(m_timerText.getLocalBounds().width / 2, m_timerText.getLocalBounds().height / 2);

    if (m_timer.getElapsedTime().asSeconds() >= Config::EXPLOSION_TIME) {
		m_exploded = true;

        if (m_exploded) {
            explode(m_position);
			
			m_isActive = false;

			if (m_timer.getElapsedTime().asSeconds() >= Config::EXPLOSION_TIME + Config::EXP_LIFE_TIME) {
				m_explosions.clear();
			}

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
//================================================
void Bomb::explode(sf::Vector2f position) {

    TextureManager& textureManager = TextureManager::instance();

    sf::Texture* texture = textureManager.getTexture('*');
    if (!texture) {
        std::cerr << "Failed to get texture for symbol: " << '*' << std::endl;
        return;
    }

	m_explosions.push_back(std::make_unique<Explosion>(*texture, position));
    m_explosions.push_back(std::make_unique<Explosion>(*texture, sf::Vector2f(position.x + Config::TILE_WIDTH, position.y)));
	m_explosions.push_back(std::make_unique<Explosion>(*texture, sf::Vector2f(position.x - Config::TILE_WIDTH, position.y)));
	m_explosions.push_back(std::make_unique<Explosion>(*texture, sf::Vector2f(position.x, position.y + Config::TILE_WIDTH)));
	m_explosions.push_back(std::make_unique<Explosion>(*texture, sf::Vector2f(position.x, position.y - Config::TILE_WIDTH)));
}
//================================================
std::vector<std::unique_ptr<Explosion>>& Bomb::getExplosions() {
	return m_explosions;
}
//================================================