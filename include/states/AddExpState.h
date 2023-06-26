#pragma once
#include "BaseState.h"
#include "Resources.h"
#include "Pokemon/Pokemon.h"
#include "entity/Player.h"
#include "Battle.h"
#include "guis/ProgressBar.h"
#include "guis/Gui.h"
#include <sstream>
class AddExpState : public BaseState
{
public:
	AddExpState(Stack<BaseState>& states, std::shared_ptr<Player> player, std::shared_ptr<Pokemon> pokemon,
				std::shared_ptr<Battle> battle) : m_player(player), m_wildPokemon(pokemon),
		m_battle(battle), m_expProgress(std::move(std::make_unique<ProgressBar>(400, 452.0f, 300, 30, sf::Color::Black, sf::Color::Blue))),
		BaseState(states),m_levelUpInfo(std::move(std::make_unique<Gui>(Resources::getInstance().getFont(), sf::Vector2f(300, 500), sf::Vector2f(500, 400))))
	
					 
	{
		entry();
	};
	~AddExpState() {};
	 void entry() {
		 m_expProgress->setProgress(m_player->getStarterPokemon()->getCurrentExpPercent());

		 m_startExpPercent = m_player->getStarterPokemon()->getCurrentExpPercent();

		  float exp = m_wildPokemon->getLevel() * 5;

		  m_player->getStarterPokemon()->setCurrentExp(m_player->getStarterPokemon()->getCurrentExp() + exp);
		
		
		 m_endExpPercent = m_player->getStarterPokemon()->getCurrentExpPercent();
		 if (m_player->getStarterPokemon()->levelUpCheck())
		 {
			 m_endExpPercent = 100.0f;
			
		 }
			
		 std::cout << "m_startExpPercent" << m_startExpPercent <<std::endl;
		 std::cout << "exp" << exp << std::endl;
		 std::cout << "m_endExpPercent" << m_endExpPercent <<std::endl;



	 }
	 void exit() {
	 
	 }
	 void update(sf::Time dt) {
		 if (!m_guiUpdateCompleted)
		 {
			 m_elapsedTime += dt;

			 // Calculate the progress based on the elapsed time
			 float progress = m_elapsedTime.asSeconds() / m_expUpdateDuration.asSeconds();

			 // Clamp the progress between 0 and 1
			 progress = std::max(0.0f, std::min(1.0f, progress));

			 // Calculate the current HP percentage based on the progress
			 float currentExp = (1 - progress) * m_startExpPercent + progress * m_endExpPercent;

			 m_expProgress->setProgress(currentExp);
			

			 // If progress is complete, set m_guiUpdateCompleted to true
			 if (progress >= 1.0f)
			 {
				
				 m_expProgress->setProgress(m_endExpPercent);
								
				 if (m_endExpPercent >= 100.0f)
				 {
					 m_battle->setAdviceText("Good job! your pokemon has leveled up!\n press Enter to continue");
					 m_levelUp = true;
					 setUpLevelUp();
					 m_elapsedTime = sf::seconds(0.0f);
				 }
				 else setStatus(false);
				 
				 m_guiUpdateCompleted = true;
			 }
		 }
		 else if (m_levelUp&& m_finish)
		 {
			 setStatus(false);
		 }
	 }
	 void setUpLevelUp()
	 {
		 m_levelUpInfo->setResetColor();
		 std::ostringstream textStream;

		 std::vector<int> levelUpInfo = m_player->getStarterPokemon()->levelUp();
		// { HPIncrease, attackIncrease, defenseIncrease, speedIncrease };
		 textStream << "New Level:" << m_player->getStarterPokemon()->getLevel() << "\n";
		 textStream << "Hp Increased by:" << levelUpInfo[0] << "\n";
		 textStream << "Attack Increased by:" << levelUpInfo[1] << "\n";
		 textStream << "Defense Increased by:" << levelUpInfo[2] << "\n";
		 textStream << "Speed Increased by:" << levelUpInfo[3] << "\n";
		 m_levelUpInfo->setText(textStream.str());
	 }
	 void handleEvents(sf::Event event) {
	 
		 if (event.type == sf::Event::KeyReleased)
		 {
			 if (event.key.code == sf::Keyboard::Enter&& m_levelUp)
			 {
				 m_finish = true;
			 }
			
		 }
	 }
	 void draw(sf::RenderWindow& window) {
		 window.setView(window.getDefaultView());
		 m_battle->draw(window);
		 m_expProgress->draw(window);
		 if (m_levelUp)
			 m_levelUpInfo->draw(window);
	 }
private:
	bool m_guiUpdateCompleted {false};
	bool m_levelUp{ false };
	float m_startExpPercent;
	float m_endExpPercent;

	

	sf::Time m_elapsedTime;
	sf::Time m_expUpdateDuration = sf::seconds(1.5f);

	std::optional<bool> m_finish {std::nullopt};

	std::shared_ptr<Pokemon> m_wildPokemon;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Battle> m_battle;
	std::unique_ptr<ProgressBar> m_expProgress;
	std::unique_ptr<Gui> m_levelUpInfo;
};

