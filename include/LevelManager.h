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


class LevelManager {
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    std::vector<std::string> m_levelFiles;
    size_t m_rows;
    size_t m_cols;
    int m_level;
    float m_tileWidth;
    float m_tileHeight;
    //TextureManager* m_bobmTexture;

    std::unique_ptr<GameObject> m_player;
    std::vector<std::unique_ptr <Enemy>> m_enemies;
    std::vector<std::unique_ptr <GameObject>> m_tempExplosion;
    Door* m_door;

public:
    LevelManager();

    //void init();
    //void setToTile(GameObject* object);
    void loadPlaylist(const std::string& filename);
    bool loadLevel();
    bool loadFromFile(const std::string& filename);
    bool nextLevel();
    std::vector<std::unique_ptr<GameObject>>& getGameObjects() ;
    const std::unique_ptr<GameObject>& getPlayer() const;
    const std::vector<std::unique_ptr <Enemy>>& getEnemies() const;
    void addBomb(sf::Vector2f position);
    void addExplosion(sf::Vector2f position);
    int getLevel() const;
    std::unique_ptr<GameObject>& getTempBomb();
    float getTileWidth() const;
    float getTileHeight() const;
    void addTheBomb(sf::Vector2f position);
    void addTheExplosion(sf::Vector2f position);
    std::vector<std::unique_ptr<GameObject>>& getTempExplosion();
    float getCols();
    size_t getRows();
    sf::Font& getFont();

    void draw(sf::RenderWindow& window);
    void removeInactiveObjects();

private:
    sf::Font m_font;
    void clear();
    void createObject(char symbol, float x, float y, sf::Font font);
    //void calcTileSize();
    void readLevelData(const std::string& filename, std::vector<std::string>& levelData);
    std::unique_ptr<GameObject> m_tempBomb;
};