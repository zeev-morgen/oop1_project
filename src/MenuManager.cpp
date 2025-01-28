#include "MenuManager.h"

MenuManager::MenuManager(sf::RenderWindow& window)
	: m_window(window)
	,m_selectedButton(0)
	, m_showHelp(false)
{
	init();
}
//===============================================
void MenuManager::init() {
	
	loadFont();
	setButtons();
	setHelpText();
}
//===============================================
void MenuManager::draw() {

	//m_window.draw(m_background);

	if (m_showHelp) {
		m_window.draw(m_helpText);
	}

	else{
		//m_window.draw(m_title);

		for (const auto& button : m_buttons) {
			m_window.draw(button);
		}
	}	
}
//===============================================
int MenuManager::handleInput() {
	sf::Event event;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			//return 2;
			m_window.close();
		}

		if (event.type == sf::Event::KeyReleased) {
			if (m_showHelp) {
				if (event.key.code == sf::Keyboard::Return) {
					m_showHelp = false;
				}
			}

			else {
				switch (event.key.code) {
				case sf::Keyboard::Up:
					m_buttons[m_selectedButton].setFillColor(sf::Color::White);
					m_selectedButton = (m_selectedButton - 1 + Config::NUM_BUTTONS_MENU) % Config::NUM_BUTTONS_MENU;
					m_buttons[m_selectedButton].setFillColor(sf::Color::Yellow);
					break;

				case sf::Keyboard::Down:
					m_buttons[m_selectedButton].setFillColor(sf::Color::White);
					m_selectedButton = (m_selectedButton + 1) % Config::NUM_BUTTONS_MENU;
					m_buttons[m_selectedButton].setFillColor(sf::Color::Yellow);
					break;

				case sf::Keyboard::Enter:
					switch (m_selectedButton) {
					case 0:  // Start Game
						return 0; 

					case 1:  // Help
						m_showHelp = true;
						break;

					case 2:  // Exit
						m_window.close();  // 2 - יציאה מהמשחק
						break;
					}
					break;
				}
			}
		}
	}
}
//===============================================
void MenuManager::loadFont() {
	// Load textures and fonts
	if (!m_font.loadFromFile("ARIAL.TTF")) {
		throw std::runtime_error("Failed to load font");
	}
}
//===============================================
void MenuManager::setButtons() {
	const std::string buttonTexts[Config::NUM_BUTTONS_MENU] = {
		"Start Game","Help","Exit" };

	for (int i = 0; i < Config::NUM_BUTTONS_MENU; ++i) {
		m_buttons[i].setFont(m_font);
		m_buttons[i].setString(buttonTexts[i]);
		m_buttons[i].setCharacterSize(30);
		m_buttons[i].setFillColor(sf::Color::White);


		//center of the buttons
		sf::FloatRect textRect = m_buttons[i].getLocalBounds();
		m_buttons[i].setOrigin(textRect.width / 2.f, textRect.height / 2.f);

		//set the buttons in the center
		float startY = m_window.getSize().y / 2.f - 60;
		m_buttons[i].setPosition(m_window.getSize().x / 2.f, startY + i * 60);
	}

	m_buttons[0].setFillColor(sf::Color::Yellow);
}
//===============================================
void MenuManager::setHelpText() {

	m_helpText.setFont(m_font);
	m_helpText.setString(
		"Game Instructions:\n\n"
		"Use arrow keys to move\n"
		"Space to jump\n"
		"Collect all coins\n"
		"Avoid enemies\n\n"
		"Press ENTER to return to menu"
	);
	m_helpText.setCharacterSize(30);
	m_helpText.setFillColor(sf::Color::White);

	sf::FloatRect textRect = m_helpText.getLocalBounds();
	m_helpText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	m_helpText.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);
}
