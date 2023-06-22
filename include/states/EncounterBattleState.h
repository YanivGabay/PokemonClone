#pragma once
#include "BaseState.h"
#include "../entity/Player.h"
#include "../Battle.h"
#include "BattleDialogState.h"

class EncounterBattleState : public BaseState
{
public:
	EncounterBattleState(Stack<BaseState>& states,
						 std::shared_ptr<Player> player,
						 std::shared_ptr<Pokemon> wildPokemon)
		: BaseState(states),
		  m_player(player),m_wildPokemon(wildPokemon),
		  m_battle(std::move(std::make_unique<Battle>(player, wildPokemon))),
		m_dialoge(std::move(std::make_unique<BattleDialogState>(getStateStack().get(),m_battle->getAdvicePosition(),m_battle->getAdviceSize())))
	
	{
		entry();
	}

	~EncounterBattleState() = default;

	 void entry() override {}
	 void exit() override
	 {
		 m_window.setView(m_originalView);
	 }

	 void update(sf::Time dt) override {
		 if(m_playerTurn)
		 m_dialoge->update(dt);

		 std::optional<BattleOptions> choice = m_dialoge->getChoice();

		 if (choice != std::nullopt)
		 {
			 m_playerTurn = false;
		 }
		 if (choice == BattleOptions::Attack)
		 {
			 //battle->triggerBackAnimation
			 //
		 }
		 if (choice == BattleOptions::Run)
		 {
			 setStatus(false);
		 }
		 
	 }
	 void handleEvents(sf::Event event) override
	 {
		 if (m_playerTurn)
			 m_dialoge->handleEvents(event);
	 }
	 void draw(sf::RenderWindow& window) override
	 {
		 m_window.setView(m_window.getDefaultView());
		 m_battle->draw(window);
		 if (m_playerTurn)
			 m_dialoge->draw(window);
	 }

private:

	bool m_playerTurn = { true };

	std::optional <BattleOptions> m_choice {std::nullopt};


	sf::RenderWindow& m_window{ Resources::getInstance().getWindow() };
	sf::View m_originalView{ m_window.getView() };
	std::unique_ptr<Battle> m_battle;

	std::unique_ptr<BattleDialogState> m_dialoge;

	std::shared_ptr<Pokemon> m_wildPokemon;

	std::shared_ptr<Player> m_player;
};
