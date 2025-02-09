#include "SmartEnemy.h"
#include "LevelManager.h"
#include <cmath>
#include "MoveableObject.h"

SmartEnemy::SmartEnemy(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, Config::ENEMY_SPEED) {
}

void SmartEnemy::update(float deltaTime, LevelManager& levelManager) {
    const Player* player = nullptr;
    for (const auto& obj : levelManager.getGameObjects()) {
        if (auto* p = dynamic_cast<Player*>(obj.get())) {
            player = p;
            break;
        }
    }

    if (player) {
        chasePlayer(*player);
    }

    avoidBombs(levelManager.getGameObjects());

    move(deltaTime, levelManager);
}

void SmartEnemy::chasePlayer(const Player& player) {
    sf::Vector2f direction = player.getPosition() - getPosition();
    if (std::abs(direction.x) >= std::abs(direction.y)) {
        direction.y = 0;  // נורמליזציה לכיוון אופקי
    } else {
        direction.x = 0;  // נורמליזציה לכיוון אנכי
    }
    if (direction.x == direction.y ) {
        direction.x = 0;
        return;
    }
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;  // נורמליזציה של הכיוון
    }
    
    m_currentDirection = direction;
}

void SmartEnemy::avoidBombs(const std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    if (isNearBomb(getPosition(), gameObjects)) {
        // שינוי כיוון להימנעות מפצצות
        m_currentDirection = -m_currentDirection;
    }
}

bool SmartEnemy::isNearBomb(const sf::Vector2f& position, const std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    const float SAFE_DISTANCE = 100.0f;
    for (const auto& obj : gameObjects) {
        if (auto bomb = dynamic_cast<Bomb*>(obj.get())) {
            float distance = std::sqrt(std::pow(position.x - bomb->getPosition().x, 2) + std::pow(position.y - bomb->getPosition().y, 2));
            if (distance < SAFE_DISTANCE) {
                return true;
            }
        }
    }
    return false;
}

void SmartEnemy::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}

//void SmartEnemy::collide(GameObject& other) {
//    other.collide(*this);
//}

void SmartEnemy::collide(Player& other) {
    // התנהגות כאשר השומר החכם מתנגש בשחקן
    other.setStatus(false);
}

void SmartEnemy::collide(Enemy& other) {
    // התנהגות כאשר השומר החכם מתנגש בשומר אחר
}

void SmartEnemy::collide(Wall& other) {
    // התנהגות כאשר השומר החכם מתנגש בקיר
}

void SmartEnemy::collide(Rock& other) {
    // התנהגות כאשר השומר החכם מתנגש בסלע
}

void SmartEnemy::collide(Door& other) {
    // התנהגות כאשר השומר החכם מתנגש בדלת
    undoMove();
}

void SmartEnemy::collide(Explosion& other) {
    // התנהגות כאשר השומר החכם מתנגש בפיצוץ
    this->setActive(false);
}

void SmartEnemy::move(float deltaTime, LevelManager& levelManager) {

    if (m_isFrozen) {
        m_freezeTimeLeft -= deltaTime;
        if (m_freezeTimeLeft <= 0) {
            m_isFrozen = false;
        }
        return;
    }

    sf::Vector2f movement = m_currentDirection * getSpeed() * deltaTime;
    movement.x = std::round(movement.x);
    movement.y = std::round(movement.y);

    sf::Vector2f newPosition = getPosition() + movement;

    if (!MoveableObject::isValidPosition(newPosition, levelManager)) {
        changeDirection(deltaTime, levelManager);
        return;
    }

    tryMove(movement, levelManager);
}