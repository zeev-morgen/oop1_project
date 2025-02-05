#include "Rock.h"

Rock::Rock(const sf::Texture& texture, const sf::Vector2f& position)
    : StaticObject(texture, position)
{
}

//need to chack if can delete this function
void Rock::update(float deltaTime, LevelManager& levelManager) {

}

void Rock::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite); 
}

//need to chack if can delete this function
void Rock::collide(Player& player) {
    player.undoMove();
}

void Rock::collide(Enemy& enemy) {
	enemy.undoMove();
	enemy.randomLocation();
}

void Rock::collide(Explosion& exp) {
	m_isActive = false;
    if (m_hasGift && m_gift) {
        // כשהאבן מתפוצצת, שחרר את המתנה
        //m_gift->setPosition(getPosition());
		m_gift->setShow(true);
        
		//add gift to level manager
    }
    //setActive(false);
}

void Rock::setGift(std::unique_ptr<Gift> gift) {
    m_gift = std::move(gift);
    if (m_gift) {
        std::cout << "gift set" << m_gift->getPosition().x << "," << m_gift->getPosition().y <<std::endl;
    }
    m_hasGift = true;
}

void Rock::setGiftIndex(size_t index) {
    m_giftIndex = index;
	m_hasGift = true;
}

size_t Rock::getGiftIndex() const {
	return m_giftIndex;
}

bool Rock::getHasGift() const {
	return m_hasGift;
}
