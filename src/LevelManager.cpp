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

    // חישוב גודל האריחים
    calcTileSize();

    // ניקוי האובייקטים הקיימים
    clear();

    // יצירת האובייקטים
    for (size_t row = 0; row < m_rows; ++row) {
        for (size_t col = 0; col < m_cols; ++col) {
            char symbol = levelData[row][col];
            if (symbol != ' ') {
                float x = col * m_tileWidth;
                float y = row * m_tileHeight;
                createObject(symbol, x, y);
            }
        }
    }

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
            sf::Sprite& sprite = object->getSprite();
            const sf::Texture* texture = sprite.getTexture();

            if (texture) {
                sf::Vector2u textureSize = texture->getSize();
                float scaleX = m_tileWidth / static_cast<float>(textureSize.x);
                float scaleY = m_tileHeight / static_cast<float>(textureSize.y);

                sprite.setScale(scaleX, scaleY);
            }

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
    sf::Texture* texture = textureManager.getTexture(symbol);;
    if (!texture) {
        std::cerr << "Failed to get texture for symbol: " << symbol << std::endl;
        return;
    }

    std::unique_ptr<GameObject> newObject = nullptr;
    sf::Vector2f position(x, y);
    
    switch (symbol) {
    case '@':  // rock
        newObject = std::make_unique<Rock>(*texture, position);
        break;

    case '!':  // enemy
        newObject = std::make_unique<Enemy>(*texture, position);
        break;

    case '#':  // wall
        newObject = std::make_unique<Wall>(*texture, position);
        break;

    case '/':  // player
    {
        auto player = std::make_unique<Player>(*texture, position);
        m_player = player.get();  // שמירת המצביע לשחקן
        newObject = std::move(player);
    }
    break;

    case 'D':  // door
    {
        auto door = std::make_unique<Door>(*texture, position);
        m_door = door.get();  // שמירת המצביע לדלת
        newObject = std::move(door);
    }
    break;
    }

    if (newObject) {
        m_gameObjects.push_back(std::move(newObject));
    }
}
//===============================================

void LevelManager::calcTileSize() {
    m_tileHeight = Config::WINDOW_HEIGHT / m_rows;
    m_tileWidth = Config::WINDOW_WIDTH / m_cols;
}
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
size_t LevelManager::getRows() const {
    return m_rows; 
}
//===============================================
size_t LevelManager::getCols() const {
    return m_cols;
}
//===============================================
void LevelManager::update(float deltaTime) {
    m_player->update(deltaTime);
}