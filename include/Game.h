#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "LevelManager.h"
#include <iostream>
#include "MenuManager.h"
//#include "TextureManager.h"

class Game {
public:
	Game();
	void run();

private:
	LevelManager m_levelManager;
	void handleEvents();
	void update(float deltaTime);
	void render();
	std::map<std::string, sf::Texture> m_textures;
	void loadTextures();
	std::unique_ptr<Player> m_player;
	std::vector<std::unique_ptr<Enemy>> m_enemies;	
	void initializeGame();
	void openMenu();
	void setBackgraund();

	sf::Sprite m_backgraund;
	sf::RenderWindow m_window;
	bool m_isRunning;
	bool m_start;

};