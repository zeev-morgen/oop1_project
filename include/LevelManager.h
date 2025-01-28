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

class LevelManager {
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    std::vector<std::string> m_levelFiles;
    size_t m_rows;
    size_t m_cols;
    int m_level;
    float m_tileWidth;
    float m_tileHeight;

    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr <Enemy>> m_enemies;
    Door* m_door;

public:
    LevelManager();

    //void init();
    void setToTile();
    void loadPlaylist(const std::string& filename);
    bool loadLevel();
    bool loadFromFile(const std::string& filename);
    bool nextLevel();
    std::vector<std::unique_ptr<GameObject>>& getGameObjects() ;
    const std::unique_ptr<Player>& getPlayer() const;
    const std::vector<std::unique_ptr <Enemy>>& getEnemies() const;

    int getLevel() const;
    float getTileWidth() const;
    float getTileHeight() const;

    float getCols();
    size_t getRows();

    void draw(sf::RenderWindow& window);

private:
    void clear();
    void createObject(char symbol, float x, float y);
    //void calcTileSize();
    void readLevelData(const std::string& filename, std::vector<std::string>& levelData);
};