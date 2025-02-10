#include "LevelManager.h"
#include <HealthGift.h>
#include <TimeGift.h>
#include <FreezeGift.h>

LevelManager::LevelManager()
: m_level(0), m_rows(0), m_cols(0), remainingTime(Config::LEVEL_TIME), m_savedPlayerScore(0), m_savedPlayerLives(Config::PLAYER_LIVES), m_numEnemies(0)

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

    startLevel();
    return true;
}
//===============================================

bool LevelManager::nextLevel() {

    m_level++;
    if (m_level >= m_levelFiles.size()) {
        std::cout << "all levels are complete\n";
        return false; //no more levels
    }

    auto playerIt = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
        [](const std::unique_ptr<GameObject>& obj) {
            return dynamic_cast<Player*>(obj.get()) != nullptr;
        });

    if (playerIt != m_gameObjects.end()) {
        auto* player = dynamic_cast<Player*>((*playerIt).get());
        player->setScore(player->getScore() + m_numEnemies * 3 + 25);
        savePlayerData(*player);
    }


    std::string currentLevelFile = m_levelFiles[m_level];
    if (!loadFromFile(currentLevelFile)) {
        throw std::runtime_error("Failed to load level: " + currentLevelFile);
    }

    auto playerIt2 = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
        [](const std::unique_ptr<GameObject>& obj) {
            return dynamic_cast<Player*>(obj.get()) != nullptr;
        });

    if (playerIt2 != m_gameObjects.end()) {
        auto* player = dynamic_cast<Player*>((*playerIt2).get());
        loadPlayerData(*player);
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
    case '@':  // Rock
    {
        auto rockPtr = std::make_unique<Rock>(*texture, position);
        Rock* rockRawPtr = rockPtr.get();
        m_gameObjects.push_back(std::move(rockPtr));
        rockToGift[rockRawPtr] = nullptr;  
    }
	break;

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
        m_numEnemies++;
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
    for (const auto& object : m_gameObjects) {
        if (!object->isActive()) {
            // אם האובייקט הוא אויב, נוסיף נקודות
            if (dynamic_cast<Enemy*>(object.get()) || dynamic_cast<SmartEnemy*>(object.get())) {
                increaseScore(Config::SCORE_GUARD);
            }

            // אם האובייקט הוא סלע, נבדוק אם יש לו מתנה במפה
            if (auto* rock = dynamic_cast<Rock*>(object.get())) {
                if (!rock->isActive()) {
                    createGift(rock);
                }
            }
        }
    }

    // מחיקת אובייקטים לא פעילים מהווקטור
    m_gameObjects.erase(
        std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
            [](const std::unique_ptr<GameObject>& obj) {
                return obj && !obj->isActive();
            }),
        m_gameObjects.end()
    );
}
//===============================================
void LevelManager::createGift(Rock* rock){

    int giftChance = rand() % 10;  

    Gift* giftPtr = nullptr;
    TextureManager& texture = TextureManager::instance();

    if (giftChance < 4) {  
        std::cout << "Gift!" << std::endl;

        char selectedGiftType;
        if (giftChance == 0) {
            selectedGiftType = 'H';  
            
            auto* giftTexture = texture.getTexture(selectedGiftType);
            auto gift = std::make_unique<HealthGift>(*giftTexture, rock->getPosition());
            giftPtr = gift.get();  
            m_gameObjects.push_back(std::move(gift)); 
            rockToGift[rock] = giftPtr;
        }

        else if (giftChance == 1) {
            selectedGiftType = 'T';   
            auto* giftTexture = texture.getTexture(selectedGiftType);
            auto gift = std::make_unique<TimeGift>(*giftTexture, rock->getPosition());
            giftPtr = gift.get();  
            m_gameObjects.push_back(std::move(gift)); 
            rockToGift[rock] = giftPtr;
        }

        else if (giftChance == 2) {
            selectedGiftType = 'F'; 
            auto* giftTexture = texture.getTexture(selectedGiftType);
            auto gift = std::make_unique<FreezeGift>(*giftTexture, rock->getPosition());
            giftPtr = gift.get();  
            m_gameObjects.push_back(std::move(gift)); 
            rockToGift[rock] = giftPtr;
        }

        else {
            selectedGiftType = '$';   
            auto* giftTexture = texture.getTexture(selectedGiftType);
            auto gift = std::make_unique<HealthGift>(*giftTexture, rock->getPosition());
            giftPtr = gift.get(); 
            m_gameObjects.push_back(std::move(gift)); 
            rockToGift[rock] = giftPtr;
        }


    }
}

//===============================================
void LevelManager::startLevel() {
    startTime = std::chrono::steady_clock::now();
    remainingTime = Config::LEVEL_TIME;
}
//===============================================
void LevelManager::updateTime() {
    auto now = std::chrono::steady_clock::now();
    remainingTime = Config::LEVEL_TIME - std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

    if (remainingTime <= 0) {
        std::cout << "Game Over! Time is up!" << std::endl;
        // ADD GAME_OVER
    }
}
//===============================================
void LevelManager::addTime(int seconds) {
    remainingTime += seconds;
    std::cout << "Bonus! +" << seconds << " seconds!" << std::endl;
}
//===============================================
int LevelManager::getTimeLeft() const {
    return remainingTime;
}

//===============================================

void LevelManager::resetLevel() {
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
//===============================================
void LevelManager::savePlayerData(Player& player) {
    m_savedPlayerScore = player.getScore();
    m_savedPlayerLives = player.getLives();
}

//===============================================
void LevelManager::loadPlayerData(Player& player) {
	player.setScore(m_savedPlayerScore);
	player.setLives(m_savedPlayerLives);
}
//===============================================
void LevelManager::increaseScore(int points) {
	auto playerIt = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) {
			return dynamic_cast<Player*>(obj.get()) != nullptr;
		});
	if (playerIt != m_gameObjects.end()) {
		auto* player = dynamic_cast<Player*>((*playerIt).get());
		player->setScore(player->getScore() + points);
	}
}