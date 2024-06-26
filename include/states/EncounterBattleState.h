#pragma once

#include "BaseState.h"
#include "../entity/Player.h"
#include "../Battle.h"
#include "BattleDialogState.h"
#include "TakeTurnState.h"
#include "AddExpState.h"


class EncounterBattleState : public BaseState
{
public:
	EncounterBattleState(Stack<BaseState>& states, std::shared_ptr<Player> player, std::shared_ptr<Pokemon> wildPokemon)
		: BaseState(states),
		  m_player(player),m_wildPokemon(wildPokemon),
		  m_battle(std::make_shared<Battle>(player, wildPokemon)),
		  m_dialoge(std::move(std::make_unique<BattleDialogState>(getStateStack().get(),m_battle->getAdvicePosition(),m_battle->getAdviceSize())))
	{
		entry();
	}

	virtual ~EncounterBattleState() = default;

	void entry() override
	{
		m_dialoge->setStatus(true);
	}

	void exit() override
	{
		m_window.setView(m_originalView);
	}

	void update(sf::Time dt) override
	{
		//if status == false player made a choice
		if (m_battle->isEnemyPokemonDead())
		{
			//so we can add exp
			// check for level up
			//if yes push expdialoge
			SoundTon::getInstance().stopSound(soundNames::BATTLE);
			SoundTon::getInstance().playSound(soundNames::WIN);
			
			auto state = std::make_unique<AddExpState>(getStateStack().get(), m_player, m_wildPokemon, m_battle);

			getStateStack().get().pushQueueState(std::move(state));
			exit();
			setStatus(false);
			
			return;
		}
		
		if (m_battle->isplayerPokemonDead())
		{
			//if other pokemon in party
			//summon them
			//else player respawing
			exit();
			setStatus(false);
			
			return;
		}

		if (m_dialoge->getStatus())
		{
			m_dialoge->update(dt);
			std::optional <BattleOptions> choice = m_dialoge->getChoice();
			
			if (choice == BattleOptions::Run)
			{	//player chose to run, quit battle
				setStatus(false);
			}
			
			if (choice == BattleOptions::Attack)
			{
				auto state = std::make_unique<TakeTurnState>(getStateStack().get(), m_battle, m_player->getStarterPokemon(), m_wildPokemon, WhosAttack::Player);
				
				getStateStack().get().pushQueueState(std::move(state));
				
				m_dialoge->setStatus(false);
				m_dialoge->resetChoice();
				
				return;
			}
		}
		else
		{
			auto state = std::make_unique<TakeTurnState>(getStateStack().get(), m_battle, m_player->getStarterPokemon(), m_wildPokemon, WhosAttack::Enemy);
			
			getStateStack().get().pushQueueState(std::move(state));
			
			m_dialoge->setStatus(true);
		}
	}
	
	void handleEvents(sf::Event event) override
	{
		if (m_dialoge->getStatus())
			m_dialoge->handleEvents(event);
	}

	void draw(sf::RenderWindow& window) override
	{
		m_window.setView(m_window.getDefaultView());
		m_battle->draw(window);
		
		if (m_dialoge->getStatus())
		{
			m_dialoge->draw(window);
		}
	}

private:
	bool m_playerTurn = { true };
	
	sf::RenderWindow& m_window{ Resources::getInstance().getWindow() };
	sf::View m_originalView{ m_window.getView() };
	std::shared_ptr<Battle> m_battle;
	std::unique_ptr<BattleDialogState> m_dialoge;
	std::shared_ptr<Pokemon> m_wildPokemon;
	std::shared_ptr<Player> m_player;
};
