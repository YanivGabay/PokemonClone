#pragma once
#include "BaseState.h"
#include "guis/Gui.h"
#include "utilities.h"

class GuideState : public BaseState
{
public:
	GuideState(Stack<BaseState>& states, sf::Vector2f cameraCenter) : BaseState(states),m_cameraCenter(cameraCenter),
		m_prompt(std::move(std::make_unique<Gui>(Resources::getInstance().getFont(), sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT),
												 sf::Vector2f(m_cameraCenter.x - SCREEN_WIDTH / 2, m_cameraCenter.y)
		))), m_currentString(guideStrings.begin())
	{
	
		m_prompt->setResetColor();
		m_prompt->setText("Welcome To MiniMons! , press Enter To Continue!");
	
	};
	~GuideState()  {};


	void entry() {
	
	};
	void exit() {
	
	};
	void update(sf::Time dt) {
	
	};
	void handleEvents(sf::Event event) {
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (m_currentString != guideStrings.end())
				{
					m_prompt->setText(*m_currentString);
					++m_currentString;
				}
				else
				{

					setStatus(false);
				}
			}
			
			
		}
	};
	void draw(sf::RenderWindow& window) {
		m_prompt->draw(window);
	};

private:
	std::vector<std::string> guideStrings = { "Use the arrows Keys to move! press enter to continue",
"Use M to open the menu, and Enter to choose option, want to go back? press M again\n you can heal your pokemon, see its stats, save the game, or quit of course\n press enter to continue",
"When you use a Portal, press enter when your on it, to transfer to the next map \n press enter to continue",
"Your goal is to train your pokemon, to Defeat the GreenNightmare,\n which reside at the Fourth Map\n",
"Have fun and enjoy!!!"



	};
	sf::Vector2f m_cameraCenter;
	std::unique_ptr<Gui> m_prompt;
	std::vector<std::string>::iterator m_currentString;
};

