#include "SmartEnemy.h"


SmartEnemy::SmartEnemy(const sf::Texture& texture, const sf::Vector2f& position)
    : MoveableObject(texture, position, Config::ENEMY_SPEED) {
}
//===============================================
void SmartEnemy::update(float deltaTime, LevelManager& levelManager) {
    const Player* player = nullptr;
    for (const auto& obj : levelManager.getGameObjects()) {
        if (auto* p = dynamic_cast<Player*>(obj.get())) {
            player = p;
            break;
        }
    }

    if (player) {
        chasePlayer(*player,levelManager);
    }

    avoidBombs(levelManager.getGameObjects());

    move(deltaTime, levelManager);
}
//===============================================
void SmartEnemy::chasePlayer(const Player& player, LevelManager& levelManager) {
    sf::Vector2f diff = player.getPosition() - getPosition();

    // close enough
    const float epsilon = 1.0f;


    sf::Vector2f newPositionX = getPosition() + sf::Vector2f((diff.x > 0) ? 1.f : -1.f, 0.f);
    sf::Vector2f newPositionY = getPosition() + sf::Vector2f(0.f, (diff.y > 0) ? 1.f : -1.f);

    if (std::abs(diff.x) > epsilon && isValidPosition(newPositionX, levelManager)) {
        m_currentDirection = sf::Vector2f((diff.x > 0) ? 1.f : -1.f, 0.f);
    }
    else if (std::abs(diff.y) > epsilon && isValidPosition(newPositionY, levelManager)) {
        m_currentDirection = sf::Vector2f(0.f, (diff.y > 0) ? 1.f : -1.f);
    }
    else {
        m_currentDirection = sf::Vector2f(0.f, 0.f);
    
    }
}
//===============================================
void SmartEnemy::avoidBombs(const std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    if (isNearBomb(getPosition(), gameObjects)) {
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
//===============================================
void SmartEnemy::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}

void SmartEnemy::collide(GameObject& other) {
    other.collide(*this);
}

void SmartEnemy::collide(Player& other) {
    other.setStatus(false);
}

void SmartEnemy::collide(Enemy& other) {
}

void SmartEnemy::collide(SmartEnemy& other) {
}



void SmartEnemy::collide(Wall& other) {
    sf::FloatRect globalBounds = other.getGlobalBounds();
    sf::Vector2f center(globalBounds.left + globalBounds.width / 2,
        globalBounds.top + globalBounds.height / 2);

    sf::Vector2f diff = getPosition() - center;

    sf::Vector2f newDiff;
    do {
        randomLocation();
        newDiff = (m_currentDirection - center);

        std::cout << "diff.x = " << diff.x << "m_currentDirection.x = " << m_currentDirection.x <<
            "diff.y = " << diff.y << "m_currentDirection.y = " << m_currentDirection.y << std::endl;

    } while (diff.x == newDiff.x || diff.y == newDiff.y);
    std::cout << "diff.x = " << diff.x << "m_currentDirection.x = " << m_currentDirection.x <<
                 "diff.y = " << diff.y << "m_currentDirection.y = " << m_currentDirection.y << std::endl;
}
//==============================================
void SmartEnemy::collide(Rock& other) {
    changeDirection();
}
//=========================================
void SmartEnemy::collide(Door& other) {
    undoMove();
	changeDirection();
}

void SmartEnemy::collide(Explosion& other) {
    SoundManager::instance().playGuard();
    this->setActive(false);
}
//===============================================
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

    int attempts = 0;
    const int maxAttempts = 4;

    while (!MoveableObject::isValidPosition(newPosition, levelManager) && attempts < maxAttempts) {
        changeDirection();
        movement = m_currentDirection * getSpeed() * deltaTime;
        newPosition = getPosition() + movement;
        attempts++;
    }

    if (attempts < maxAttempts) {
        tryMove(movement, levelManager);
    }
    else {
        m_currentDirection = -m_currentDirection;
    }
}
//===============================================
void SmartEnemy::randomLocation() {
	
		const sf::Vector2f possibleDirections[] = {
				{1.0f, 0.0f}, {-1.0f, 0.0f},
				{0.0f, 1.0f}, {0.0f, -1.0f}
		};
		m_currentDirection = possibleDirections[rand() % 4];
	
}