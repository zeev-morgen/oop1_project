#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIManager {
private:
    sf::Font m_font;
    sf::Text m_healthText;
    sf::Text m_scoreText;
    sf::Text m_timerText;

public:
    UIManager() {
        if (!m_font.loadFromFile("ARIAL.TTF")) {
            std::cerr << "Error: Could not load font arial.ttf!" << std::endl;
        }

        
        m_healthText.setFont(m_font);
        m_healthText.setCharacterSize(30);
        m_healthText.setFillColor(sf::Color::Red);
        m_healthText.setPosition(50.f, 5.f);

        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(30);
        m_scoreText.setFillColor(sf::Color::White);
        m_scoreText.setPosition(300.f, 5.f);

        m_timerText.setFont(m_font);
        m_timerText.setCharacterSize(30);
        m_timerText.setFillColor(sf::Color::Green);
        m_timerText.setPosition(550.f, 5.f);
    }

    
    void update(int health, int score, float time) {
        m_healthText.setString("LIVE: " + std::to_string(health));
        m_scoreText.setString("SCORE: " + std::to_string(score));
        m_timerText.setString("TIMER: " + std::to_string(static_cast<int>(time)));
    }

    
    void drawUI(sf::RenderWindow& window) {
        window.draw(m_healthText);
        window.draw(m_scoreText);
        window.draw(m_timerText);
    }
};
