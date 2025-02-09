#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include "GameObject.h"
#include "TextureManager.h"
#include "config.h"
#include "Player.h"
#include "Enemy.h"
#include "Rock.h"
#include "Wall.h"
#include "Door.h"
#include "Bomb.h"
#include "Explosion.h"
#include "SoundManager.h"
#include <iostream>
#include "Gift.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include "SmartEnemy.h"
#include <unordered_map>

class LevelManager {
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    std::vector<std::string> m_levelFiles;

    size_t m_rows;
    size_t m_cols;
    int m_level;
    int m_savedPlayerScore;
    int m_savedPlayerLives;
	int m_numEnemies;

    

    sf::Font m_font;
    void clear();
    void createObject(char symbol, float x, float y);
    void readLevelData(const std::string& filename, std::vector<std::string>& levelData);

public:
    LevelManager();
    std::unordered_map<Rock*, Gift*> rockToGift;
    int remainingTime;
    void loadPlaylist(const std::string& filename);
    bool loadLevel();
    bool loadFromFile(const std::string& filename);
    bool nextLevel();
    std::vector<std::unique_ptr<GameObject>>& getGameObjects() ;
    int getLevel() const;
    size_t getCols();
    size_t getRows()const;
    sf::Font& getFont();
    void draw(sf::RenderWindow& window);
    void removeInactiveObjects();
    void resetLevel();
    void freezeAllEnemies(float duration);
	std::unique_ptr<GameObject>& getPlayer();

    std::chrono::time_point<std::chrono::steady_clock> startTime;
    void updateTime();
    int getTimeLeft()const;
    void startLevel();
    void addTime(int seconds);
	void savePlayerData(Player& player);
	void loadPlayerData(Player& player);
    void increaseScore(int points);
};