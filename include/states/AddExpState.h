#pragma once
#include "BaseState.h"
#include "Resources.h"
#include "Pokemon/Pokemon.h"
#include "entity/Player.h"
#include "Battle.h"
#include "guis/ProgressBar.h"
class AddExpState : public BaseState
{
public:
	AddExpState(Stack<BaseState>& states, std::shared_ptr<Player> player, std::shared_ptr<Pokemon> pokemon,
				std::shared_ptr<Battle> battle) : m_player(player), m_wildPokemon(pokemon),
		m_battle(battle), m_expProgress(std::move(std::make_unique<ProgressBar>(400, 452.0f, 200, 50, sf::Color::Black, sf::Color::Blue))),
		BaseState(states)
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
								
				
				 m_guiUpdateCompleted = true;
			 }
		 }
		 else
		 {
			 setStatus(false);
		 }
	 }
	 void handleEvents(sf::Event event) {
	 
	 }
	 void draw(sf::RenderWindow& window) {
		 window.setView(window.getDefaultView());
		 m_battle->draw(window);
		 m_expProgress->draw(window);
	 }
private:
	bool m_guiUpdateCompleted {false};

	float m_startExpPercent;
	float m_endExpPercent;

	sf::Time m_elapsedTime;
	sf::Time m_expUpdateDuration = sf::seconds(1.5f);


	std::shared_ptr<Pokemon> m_wildPokemon;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Battle> m_battle;
	std::unique_ptr<ProgressBar> m_expProgress;
};

