//#include "GameUI.h"
//
//void GameUI::init() {
//    if (!m_font.loadFromFile("ARIAR.TTF")) {
//        throw std::runtime_error("Failed to load font!");
//    }
//
//    // הגדרת הרקע ל-UI
//    m_uiBackground.setSize(sf::Vector2f(800.f, UI_HEIGHT));
//    m_uiBackground.setFillColor(sf::Color(0, 0, 0, 200));
//    m_uiBackground.setPosition(0, 0);
//
//    // הגדרת טקסט הניקוד
//    m_scoreText.setFont(m_font);
//    m_scoreText.setCharacterSize(20);
//    m_scoreText.setFillColor(sf::Color::White);
//    m_scoreText.setPosition(10, 10);
//
//    // הגדרת טקסט החיים
//    m_livesText.setFont(m_font);
//    m_livesText.setCharacterSize(20);
//    m_livesText.setFillColor(sf::Color::White);
//    m_livesText.setPosition(200, 10);
//
//    // הגדרת טקסט השלב
//    m_levelText.setFont(m_font);
//    m_levelText.setCharacterSize(20);
//    m_levelText.setFillColor(sf::Color::White);
//    m_levelText.setPosition(400, 10);
//
//    // הגדרת טקסט הטיימר
//    m_timerText.setFont(m_font);
//    m_timerText.setCharacterSize(20);
//    m_timerText.setFillColor(sf::Color::White);
//    m_timerText.setPosition(600, 10);
//}
//
//// פונקציה להתחלת טיימר חדש
//void GameUI::startLevelTimer(float timeLimit) {
//    m_levelTimeLimit = timeLimit;
//    m_remainingTime = timeLimit;
//    m_levelClock.restart();
//}
//
//// פונקציה לעדכון הטיימר
//void GameUI::updateTimer() {
//    if (m_remainingTime > 0) {
//        m_remainingTime = m_levelTimeLimit - m_levelClock.getElapsedTime().asSeconds();
//        if (m_remainingTime < 0) m_remainingTime = 0;
//
//        // המרת הזמן לפורמט דקות:שניות
//        int minutes = static_cast<int>(m_remainingTime) / 60;
//        int seconds = static_cast<int>(m_remainingTime) % 60;
//
//        // עדכון טקסט הטיימר
//        std::stringstream ss;
//        ss << "Time: ";
//        ss << std::setfill('0') << std::setw(2) << minutes << ":";
//        ss << std::setfill('0') << std::setw(2) << seconds;
//        m_timerText.setString(ss.str());
//
//        // שינוי צבע כשנשאר מעט זמן
//        if (m_remainingTime < 10.0f) {
//            m_timerText.setFillColor(sf::Color::Red);
//        }
//    }
//}
//
//float GameUI::getUIHeight() const {
//    return UI_HEIGHT; 
//}
//
//void GameUI::update(int score, int lives, int level) {
//    m_scoreText.setString("Score: " + std::to_string(score));
//    m_livesText.setString("Lives: " + std::to_string(lives));
//    m_levelText.setString("Level: " + std::to_string(level));
//    updateTimer();
//}
//
//void GameUI::draw(sf::RenderWindow& window) {
//    window.draw(m_uiBackground);
//    window.draw(m_scoreText);
//    window.draw(m_livesText);
//    window.draw(m_levelText);
//    window.draw(m_timerText);
//}
//
//bool GameUI::isTimeUp() const {
//    return m_remainingTime <= 0;
//}