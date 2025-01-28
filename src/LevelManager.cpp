#include "LevelManager.h"
#include "config.h"
#include <iostream>

LevelManager::LevelManager()
	: m_level(0), m_rows(0), m_cols(0), m_player(nullptr), m_door(nullptr)
{
    loadPlaylist("Playlist.txt");
    loadLevel();
}
//===============================================

void LevelManager::loadPlaylist(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open playlist file: " + filename);
    }

    std::string levelFile;
    while (std::getline(file, levelFile)) {
        if (!levelFile.empty()) {
            m_levelFiles.push_back(levelFile);
        }
    }
    file.close();

    if (m_levelFiles.empty()) {
        throw std::runtime_error("No levels found in playlist.");
    }
}
//===============================================

bool LevelManager::loadLevel() {
    if (m_level >= m_levelFiles.size()) {
        std::cout << "all levels are complete\n";
        return false; //no more levels
    }

    std::string currentLevelFile = m_levelFiles[m_level];
    if (!loadFromFile(currentLevelFile)) {
        throw std::runtime_error("Failed to load level: " + currentLevelFile);
    }

    return true;
}
//===============================================

bool LevelManager::loadFromFile(const std::string& filename) {
    std::vector<std::string> levelData;
    readLevelData(filename, levelData);

    //calcTileSize();
    clear();

    for (size_t row = 0; row < m_rows; ++row) {
        for (size_t col = 0; col < m_cols; ++col) {
            char symbol = levelData[row][col];
            if (symbol != ' ') {
                float x = col * Config::TILE_WIDTH;
                float y = row * Config::TILE_HEIGHT;
                createObject(symbol, x, y);
                //std::cout << x << "," << y << "\n";

            }
        }
    }

    setToTile();

    return true;
}
//===============================================

bool LevelManager::nextLevel() {

    m_level++;
    if (m_level >= m_levelFiles.size()) {
        std::cout << "all levels are complete\n";
        return false; //no more levels
    }

    std::string currentLevelFile = m_levelFiles[m_level];
    if (!loadFromFile(currentLevelFile)) {
        throw std::runtime_error("Failed to load level: " + currentLevelFile);
    }

    return true;
}
//===============================================

int LevelManager::getLevel()const {
    return m_level;
}
//===============================================

void LevelManager::draw(sf::RenderWindow& window) {

    for (const auto& object : m_gameObjects) {
        if (object && object->isActive()) {
            object->draw(window);
        }
    }
}
//===============================================
void LevelManager::clear() {
    m_gameObjects.clear();
    m_player = nullptr; 
    m_door = nullptr;
}
//===============================================

void LevelManager::createObject(char symbol, float x, float y) {
    TextureManager& textureManager = TextureManager::instance();
    textureManager.loadGameTextures();
    sf::Texture* texture = textureManager.getTexture(symbol);
    if (!texture) {
        std::cerr << "Failed to get texture for symbol: " << symbol << std::endl;
        return;
    }

    sf::Vector2f position(x, y);

    switch (symbol) {
    case '@':  // rock
    {
        m_gameObjects.push_back(std::make_unique<Rock>(*texture, position));
    }
    break;

    case '!':
    {
        //m_enemies.push_back(std::make_unique<Enemy>(*texture, position));
        m_gameObjects.push_back(std::make_unique<Enemy>(*texture, position));
    }
    break;

    case '/':
    {
        //m_player = std::make_unique<Player>(*texture, position);
        m_gameObjects.push_back(std::make_unique<Player>(*texture, position));
    }
    break;

    case '#':  // wall
    {
        m_gameObjects.push_back(std::make_unique<Wall>(*texture, position));
    }
    break;

    case 'D':  // door
    {
        m_gameObjects.push_back(std::make_unique<Door>(*texture, position));
    }
    break;
    }
}
//===============================================
//
//void LevelManager::calcTileSize() {
//    m_tileHeight = Config::WINDOW_HEIGHT / m_rows;
//    m_tileWidth = Config::WINDOW_WIDTH / m_cols;
//}
//===============================================

void LevelManager::readLevelData(const std::string& filename, std::vector<std::string>& levelData) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open level file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            levelData.push_back(line);
        }
    }

    if (levelData.empty()) {
        throw std::runtime_error("Empty level file: " + filename);
    }

    m_rows = levelData.size();
    m_cols = levelData[0].length();
}
//===============================================
float LevelManager::getTileWidth() const {
    return m_tileWidth;
}
//===============================================
float LevelManager::getTileHeight() const {
    return m_tileHeight;
}
//===============================================
 size_t LevelManager::getRows()  {
    return m_rows; 
}
//===============================================
float LevelManager::getCols()  {
    return m_cols;
}
//===============================================
//void LevelManager::update(float deltaTime) {
//    m_player->update(deltaTime);
//}
//===============================================
std::vector<std::unique_ptr<GameObject>>& LevelManager::getGameObjects()  {
    return m_gameObjects;
}
//===============================================
const std::unique_ptr<Player>& LevelManager::getPlayer() const {
    return m_player;
}
//===============================================
const std::vector<std::unique_ptr<Enemy>>& LevelManager::getEnemies() const {
    return m_enemies;
}
//===============================================
void LevelManager::setToTile() {
    auto &obj = getGameObjects();
    for (const auto& object : obj) {
        object->setToTile(Config::TILE_HEIGHT, Config::TILE_HEIGHT);
    }
}