#include "LevelManager.h"
#include <HealthGift.h>
#include <TimeGift.h>
#include <FreezeGift.h>

LevelManager::LevelManager()
    : m_level(0), m_rows(0), m_cols(0)
{
    TextureManager& textureManager = TextureManager::instance();
    textureManager.loadGameTextures();

    loadPlaylist("Playlist.txt");
    m_font.loadFromFile("ARIAL.TTF");
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
                float x = static_cast<float>(col) * Config::TILE_WIDTH;
                float y = static_cast<float>(row) * Config::TILE_HEIGHT + Config::UI;
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
            object->draw(window);
        }
    }
}
//===============================================
void LevelManager::clear() {
    m_gameObjects.clear();
}
//===============================================

void LevelManager::createObject(char symbol, float x, float y) {
    TextureManager& textureManager = TextureManager::instance();
    
    sf::Texture* texture = textureManager.getTexture(symbol);
    if (!texture) {
        std::cerr << "Failed to get texture for symbol: " << symbol << std::endl;
        return;
    }

    sf::Vector2f position(x, y);

    switch (symbol) {
    case '@':  // rock
    {
        auto rockPtr = std::make_unique<Rock>(*texture, position);

        if (rand() % 4 == 0) { 
            int giftType = rand() % 4;

            switch (giftType) {

            case 0:
                texture = textureManager.getTexture('$');
                m_gameObjects.push_back(std::make_unique<Gift>(*texture, position));
				rockPtr->setGiftIndex(m_gameObjects.size() - 1);
				std::cout << "gift index: " << m_gameObjects.size() - 1 << std::endl;
                break;

            case 1:
                texture = textureManager.getTexture('T');
                m_gameObjects.push_back(std::make_unique<Gift>(*texture, position));
				rockPtr->setGiftIndex(m_gameObjects.size() - 1);
				std::cout << "gift index: " << m_gameObjects.size() - 1 << std::endl;
                break;

            case 2:
                texture = textureManager.getTexture('H');
                m_gameObjects.push_back(std::make_unique<Gift>(*texture, position));
				rockPtr->setGiftIndex(m_gameObjects.size() - 1);
				std::cout << "gift index: " << m_gameObjects.size() - 1 << std::endl;
                break;
            
            case 3:
				texture = textureManager.getTexture('F');
                m_gameObjects.push_back(std::make_unique<Gift>(*texture, position));
                rockPtr->setGiftIndex(m_gameObjects.size() - 1);
                std::cout << "gift index: " << m_gameObjects.size() - 1 << std::endl;
                break;
            }  
        }
        m_gameObjects.push_back(std::move(rockPtr));
        break;
    }

	case '!':  // enemy
    {
        int enemyType = rand() % 2;

        switch (enemyType) {

        case 0:
            m_gameObjects.push_back(std::make_unique<SmartEnemy>(*texture, position));
            break;

        case 1:
            m_gameObjects.push_back(std::make_unique<Enemy>(*texture, position));
            break;
        }
    }
    break;


	case '/':  // player
    {
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
 size_t LevelManager::getRows() const {
    return m_rows; 
}
//===============================================
size_t LevelManager::getCols()  {
    return m_cols;
}
//===============================================
std::vector<std::unique_ptr<GameObject>>& LevelManager::getGameObjects()  {
    return m_gameObjects;
}
//===============================================
sf::Font& LevelManager::getFont() {
    return m_font;
}
//===============================================
void LevelManager::removeInactiveObjects() {
    auto& objects = m_gameObjects;
	
    for (size_t i = 0; i < objects.size(); i++) {
        if (!objects[i]->isActive()) {
            if (auto* rock = dynamic_cast<Rock*>(objects[i].get())) {
                size_t giftIndex = rock->getGiftIndex();
                
                if (rock->getHasGift() && giftIndex < objects.size()) {                    
                    objects[giftIndex-2]->setShow(true);
                }
            }
        }
    }

    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [](const std::unique_ptr<GameObject>& obj) {
                return obj && !obj->isActive();
            }),
        objects.end()
    );

}
//===============================================
void LevelManager::clearAllBombs() {
    // מחיקת כל הפצצות מהמשחק
    auto& gameObjects = getGameObjects();
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const auto& obj) {
                return dynamic_cast<Bomb*>(obj.get()) != nullptr;
            }
        ),
        gameObjects.end()
    );
}

//===============================================
void LevelManager::resetLevel() {
	clearAllBombs();
	loadLevel();
    
}
//===============================================
void LevelManager::freezeAllEnemies(float duration) {
    for (auto& obj : m_gameObjects) {
        if (auto* enemy = dynamic_cast<Enemy*>(obj.get())) {
            enemy->freeze(duration);
        }
    }
}
//===============================================
std::unique_ptr<GameObject>& LevelManager::getPlayer() {
	auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return dynamic_cast<Player*>(obj.get()) != nullptr;
		});
	if (it == m_gameObjects.end()) {
		throw std::runtime_error("Player not found in game objects.");
	}
	return *it;
}