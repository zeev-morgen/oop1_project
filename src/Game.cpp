#include "Game.h"

Game::Game()

	: m_window(sf::VideoMode(m_levelManager.getCols()* Config::TILE_HEIGHT, m_levelManager.getRows()* Config::TILE_HEIGHT + Config::UI), "SFML Game")
	, m_isRunning(true)
	, m_gameObjects(m_levelManager.getGameObjects())
	, uiManager()
{
	m_window.setFramerateLimit(60);
	saveInitialPositions();
}
//===============================================
void Game::run() {
	openMenu();
	sf::Clock clock;
	loadTextures();
	while (m_window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		handleEvents();
		update(deltaTime, m_levelManager);
		render();
	}
}
//===============================================
void Game::loadTextures() {
	TextureManager& textureManager = TextureManager::instance();
	textureManager.loadGameTextures();
}
//===============================================
void Game::openMenu() {
	MenuManager menu(m_window);
	while (m_window.isOpen()) {

		m_window.clear();
		int menuChoice = menu.handleInput();
		if (menuChoice == 0) {
			return;
		}

		menu.draw();
		m_window.display();
	}
}
//===============================================
void Game::draw() {

	for (const auto& object : m_levelManager.getGameObjects()) {
		if (object) {
			object->draw(m_window);
		}
	}
}
//===============================================
void Game::update(float deltaTime, LevelManager& levelManager) {
	
	for (const auto& object : m_levelManager.getGameObjects()) {
		if (object) {
			object->update(deltaTime, levelManager);
		}
	}
	

	if (auto& tempBomb = m_levelManager.getTempBomb()) {
		m_levelManager.addTheBomb(tempBomb->getPosition());
	}

	const auto& tempExplosion = m_levelManager.getTempExplosion();

	for (const auto& exp : tempExplosion) {
		if (exp) {
			m_levelManager.addTheExplosion(exp->getPosition());
		}
	}

	m_levelManager.getTempExplosion().clear();
	handleCollisions();
	updatePlayerData();
	m_levelManager.removeInactiveObjects();
	isLevelComplete();
}


//===============================================
void Game::render() {
	m_window.clear(sf::Color::Black);
	draw();

	uiManager.drawUI(m_window);

	m_window.display();
}

//===============================================
void Game::handleEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_isRunning = false;
			m_window.close();
		}
	}
}
//===============================================
void Game::handleCollisions() {
    
    for (size_t i = 0; i < m_gameObjects.size(); ++i) {
        for (size_t j = i + 1; j < m_gameObjects.size(); ++j) {
            if (m_gameObjects[i]->getBounds().intersects(m_gameObjects[j]->getBounds())) {
                m_gameObjects[i]->collide(*m_gameObjects[j]);
                m_gameObjects[j]->collide(*m_gameObjects[i]);
            }
        }
    }
}
//===============================================
void Game::saveInitialPositions() {

	for (const auto& obj : m_gameObjects) {
		if (obj) {
			m_initialPositions[obj.get()] = obj->getPosition();
		}
	}
}
//===============================================
void Game::resetPositions() {

	for (const auto& obj : m_gameObjects) {
		if (obj && obj->isActive()) {
			auto it = m_initialPositions.find(obj.get());
			if (it != m_initialPositions.end()) {
				obj->setPosition(it->second);
			}
		}
	}
}
//===============================================
void Game::recreateWindow() {
	float newWidth = m_levelManager.getCols() * Config::TILE_WIDTH;
	float newHeight = m_levelManager.getRows() * Config::TILE_HEIGHT + Config::UI;

	m_window.close();
	m_window.create(sf::VideoMode(newWidth, newHeight), "SFML Game");
	m_window.setFramerateLimit(60);
}
//===============================================
void Game::isLevelComplete(){
	auto& gameObjects = m_levelManager.getGameObjects();
	auto playerIt = std::find_if(gameObjects.begin(), gameObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return dynamic_cast<Player*>(obj.get()) != nullptr;
		});

	if (playerIt != gameObjects.end()) {
		auto* player = dynamic_cast<Player*>((*playerIt).get());

		if (player->getFinish()) {
			if (m_levelManager.nextLevel()) {
				recreateWindow();
				m_initialPositions.clear();
				saveInitialPositions();
			}
			else {
				m_isRunning = false;
				m_window.close();
			}
		}
	}
}
//===============================================
void Game::updatePlayerData() {
	auto& gameObjects = m_levelManager.getGameObjects();

	auto playerIt = std::find_if(gameObjects.begin(), gameObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return dynamic_cast<Player*>(obj.get()) != nullptr;
		});

	if (playerIt != gameObjects.end()) {
		auto* player = dynamic_cast<Player*>((*playerIt).get());

		uiManager.update(player->getLives(), player->getScore(), 54);

		if (!player->getStatus()) {
			resetGameState();
			player->setStatus(true);
		}
	}
}
//===============================================
void Game::resetGameState() {
	resetPositions();

	m_levelManager.clearAllBombs();
	m_levelManager.getTempExplosion().clear();

}
