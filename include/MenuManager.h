#include <SFML/Graphics.hpp>
#include "Config.h"

class MenuManager {
private:
	sf::RenderWindow& m_window;
	sf::Font m_font;
	sf::Text m_buttons[Config::NUM_BUTTONS_MENU];
	sf::Sprite m_background;
	sf::Text m_helpText;
	sf::Text m_title;
	sf::RectangleShape m_highlightBox;

	int m_selectedButton;
	bool m_showHelp;
	void loadFont();
	void setButtons();
	void setHelpText();

public:
	MenuManager(sf::RenderWindow& window);
	void init();
	void draw();
	int handleInput();
};