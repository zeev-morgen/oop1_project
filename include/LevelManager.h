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
#include <iostream>
#include "Gift.h"


class LevelManager {
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    std::vector<std::string> m_levelFiles;
    std::vector<std::unique_ptr <GameObject>> m_tempExplosion;
    std::unique_ptr<GameObject> m_tempBomb;
    std::unique_ptr<GameObject> m_tempGift;

    size_t m_rows;
    size_t m_cols;
    int m_level;

public:
    LevelManager();

    void loadPlaylist(const std::string& filename);
    bool loadLevel();
    bool loadFromFile(const std::string& filename);
    bool nextLevel();
    std::vector<std::unique_ptr<GameObject>>& getGameObjects() ;
    void addBomb(sf::Vector2f position);
    void addExplosion(sf::Vector2f position);
    int getLevel() const;
    std::unique_ptr<GameObject>& getTempBomb();
    void addTheBomb(sf::Vector2f position);
    void addTheExplosion(sf::Vector2f position);
    std::vector<std::unique_ptr<GameObject>>& getTempExplosion();
    size_t getCols();
    size_t getRows()const;
    sf::Font& getFont();
    void clearAllBombs();


    void draw(sf::RenderWindow& window);
    void removeInactiveObjects();

private:
    sf::Font m_font;
    void clear();
    void createObject(char symbol, float x, float y, sf::Font font);
    void readLevelData(const std::string& filename, std::vector<std::string>& levelData);
};