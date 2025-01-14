#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class Game {
public:
	Game();
	void run();

private:
	void handleEvents();
	void update(float deltaTime);
	void render();
	std::map<std::string, sf::Texture> m_textures;
	void loadTextures();
	std::unique_ptr<Player> m_player;
	std::vector<std::unique_ptr<Enemy>> m_enemies;	
	void initializeGame();
	void createEnemies();

	sf::RenderWindow m_window;
	bool m_isRunning;
};