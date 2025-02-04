#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "LevelManager.h"
#include <iostream>
#include "MenuManager.h"
#include "UIManager.h"

class Game {
public:
	Game();
	void run();

private:
	LevelManager m_levelManager;
	UIManager uiManager;
	sf::Clock m_timerClock;
	float m_timeLeft;
	const float LEVEL_TIME = 60.0f;


	void handleEvents();
	void update(float deltaTime, LevelManager& levelManager);
	void render();
	void loadTextures();
	void openMenu();
	void draw();
	void handleCollisions();
	Player* GetPlayer();

	std::vector<std::unique_ptr<GameObject>>& m_gameObjects;
	std::map<std::string, sf::Texture> m_textures;
	std::unique_ptr<Player> m_player;
	

	sf::Sprite m_backgraund;
	sf::RenderWindow m_window;

	bool m_isRunning;
	bool m_start;
};