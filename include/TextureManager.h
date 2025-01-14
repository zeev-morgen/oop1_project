#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
public:
    static TextureManager& instance();
    bool loadTexture(char id, const std::string& path);
    void loadGameTextures();
    sf::Texture* getTexture(char id);

private:
    TextureManager() = default;
    std::unordered_map<char, sf::Texture> m_textures;
};