#include "Game.h"

Game::Game()
	: m_window(sf::VideoMode(1000, 800), "SFML Game")
	, m_isRunning(true) 
{
	m_window.setFramerateLimit(60);
	TextureManager::instance().loadGameTextures();
	setBackgraund();
	initializeGame();
	//m_levelManager.init();
}

void Game::handleEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_isRunning = false;
			m_window.close();
		}
	}
}

void Game::update(float deltaTime) {
	m_levelManager.update(deltaTime);
}

void Game::render() {
	m_window.clear(sf::Color::Black);
	//m_window.draw(m_backgraund);
	m_levelManager.draw(m_window);

	m_window.display();
}

void Game::run() {
	openMenu();
	sf::Clock clock;
	while (m_window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		handleEvents();
		update(deltaTime);
		render();
	}
}

void Game::loadTextures() {
	TextureManager& textureManager = TextureManager::instance();
	textureManager.loadGameTextures();
}

void Game::initializeGame() {
	
}

void Game::openMenu() {
	MenuManager menu(m_window);
	while (m_window.isOpen()) {

		m_window.clear();
		int menuChoice = menu.handleInput();
		if (menuChoice == 0) {         // Start Game
			return;                  // הרץ את המשחק
		}

		menu.draw();
		m_window.display();
	}
}

void Game::setBackgraund() {
	sf::Texture* backgroundTexture = TextureManager::instance().getTexture('^');
	if (backgroundTexture) {
		m_backgraund.setTexture(*backgroundTexture);
	}
	else {
		// Handle the error, e.g., log it or set a default texture
		std::cerr << "Error: Background texture not found!" << std::endl;
	}
}
