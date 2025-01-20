#include "TextureManager.h"
#include <iostream>
#include <filesystem>


TextureManager& TextureManager::instance() {
    static TextureManager instance;
    return instance;
}

bool TextureManager::loadTexture(char id, const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        return false;
    }
    m_textures[id] = std::move(texture);
    return true;
}

sf::Texture* TextureManager::getTexture(char id) {
    auto it = m_textures.find(id);
    return (it != m_textures.end()) ? &it->second : nullptr;
}

void TextureManager::loadGameTextures() {
    
    loadTexture('#', "wall.jpg");    
    loadTexture('@', "rock.jpg");    
    loadTexture('!', "enemy.jpg");   
    loadTexture('*', "explode.jpg");  
    loadTexture('%', "boomb.jpg");  
    loadTexture('/', "player.jpg");
    loadTexture('$', "gift.jpg");
	loadTexture('^', "backgraund.jpg");
    loadTexture('D', "door.jpg");
}
