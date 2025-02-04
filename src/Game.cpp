#include "Game.h"

Game::Game()
	: m_window(sf::VideoMode(m_levelManager.getCols() * Config::TILE_HEIGHT, m_levelManager.getRows() * Config::TILE_HEIGHT + Config::UI_HEIGHT), "SFML Game")
	, m_isRunning(true)
	, m_gameObjects(m_levelManager.getGameObjects())

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

	auto& gameObjects = m_levelManager.getGameObjects();
	auto playerIt = std::find_if(gameObjects.begin(), gameObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return dynamic_cast<Player*>(obj.get()) != nullptr;
		});

	if (playerIt != gameObjects.end()) {
		auto* player = dynamic_cast<Player*>((*playerIt).get());

		if (!player->isActive()) {
			player->setActive(true);
			resetPositions();
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
	m_levelManager.removeInactiveObjects();
	
	handleCollisions();

	auto& gameObjects2 = m_levelManager.getGameObjects();
	auto playerIt2 = std::find_if(gameObjects.begin(), gameObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return dynamic_cast<Player*>(obj.get()) != nullptr;
		});

	if (playerIt2 != gameObjects.end()) {
		auto* player = dynamic_cast<Player*>((*playerIt2).get());
	
		if (player->getFinish()) {
			if (levelManager.nextLevel()) {
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
void Game::render() {
	m_window.clear(sf::Color::Black);
	draw();
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
	// שמירת מיקומים של כל האובייקטים
	for (const auto& obj : m_gameObjects) {
		if (obj) {
			m_initialPositions[obj.get()] = obj->getPosition();
		}
	}
}
//===============================================
void Game::resetPositions() {
	// החזרת כל האובייקטים למיקומם ההתחלתי
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
	float newHeight = m_levelManager.getRows() * Config::TILE_HEIGHT;

	m_window.close();
	m_window.create(sf::VideoMode(newWidth, newHeight), "SFML Game");
	m_window.setFramerateLimit(60);
}
//===============================================

