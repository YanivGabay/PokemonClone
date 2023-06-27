#pragma once

#include "BaseState.h"
#include "guis/Gui.h"
#include "entity/Player.h"
#include "PokemonMenuState.h"
#include "saveManager.h"
#include "SoundTon.h"
#include "utilities.h"


class PlayState;

enum PlayerMenuOptions
{
	Pokemons,
	Heal,
	SaveGame,
	QuitGame
};

const int PlayerMenuSize = 4;

std::optional<PlayerMenuOptions> operator++(std::optional<PlayerMenuOptions> option)
{
	if (option)
	{
		*option = static_cast<PlayerMenuOptions>((static_cast<int>(*option) + 1) % PlayerMenuSize);
	}

	return option;
}

std::optional<PlayerMenuOptions> operator--(std::optional<PlayerMenuOptions> option)
{
	if (option)
	{
		int value = static_cast<int>(*option) - 1;
		
		if (value < 0)
		{
			value = PlayerMenuSize - 1;
		}
		
		*option = static_cast<PlayerMenuOptions>(value);
	}

	return option;
}


class PlayerMenuState : public BaseState
{
public:
	PlayerMenuState(Stack<BaseState>& states, saveManager& manager,sf::Vector2f cameraCenter, std::shared_ptr<Player> player)
		: BaseState(states),
		m_saveGame(manager),
		m_cameraCenter(cameraCenter),
		m_player(player)
	{
		SoundTon::getInstance().stopSound(soundNames::CITY);
		SoundTon::getInstance().playSound(soundNames::MENU_THEME);
		entry();
	}
	
	virtual ~PlayerMenuState()
	{
		SoundTon::getInstance().stopSound(soundNames::MENU_THEME);
		SoundTon::getInstance().playSound(soundNames::CITY);
	}


	 void entry()
	 {
		 sf::Vector2f buttonSize = sf::Vector2f(m_windowSize.x / 3, m_windowSize.y / 6);
		 
		 for (size_t i = 0; i < PlayerMenuSize; i++)
		 {
			 m_menuSelection[i] = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(), buttonSize, sf::Vector2f(m_cameraCenter.x+m_windowSize.x/2-buttonSize.x,m_cameraCenter.y-m_windowSize.y/2+50*i)));
		 }

		 resetText();
	 }
	 
	 void resetText()
	 {
		 m_menuSelection[PlayerMenuOptions::Pokemons]->setText("Pokemons");
		 m_menuSelection[PlayerMenuOptions::Heal]->setText("Heal");
		 m_menuSelection[PlayerMenuOptions::SaveGame]->setText("SaveGame");
		 m_menuSelection[PlayerMenuOptions::QuitGame]->setText("QuitGame");
	 }
	 
	 void exit() {}
	 
	 void update(sf::Time dt)
	 {
		 PlayerMenuOptions option = m_hover.value();
		 
		 for (int i = 0; i < PlayerMenuSize; i++)
		 {
			 if (i == option)
			 {
				 m_menuSelection[i]->setHoverColor();
			 }
			 else
			 {
				 m_menuSelection[i]->setResetColor();
			 }
		 }

		 if (m_selection == Pokemons)
		 {
			 auto state = std::make_unique<PokemonMenuState>(getStateStack().get(), m_player, m_cameraCenter);
			 
			 getStateStack().get().pushQueueState(std::move(state));
			 
			 SoundTon::getInstance().playSound(soundNames::CLICK);
			 
			 m_selection = std::nullopt;
		 }
		 else if (m_selection == SaveGame)
		 {
			 m_saveGame.savingIntoFile();
			 
			 SoundTon::getInstance().playSound(soundNames::SAVING);
			 
			 m_selection = std::nullopt;
		 }
		 else if (m_selection == Heal)
		 {
			 m_player->healPokemons();
			 
			 SoundTon::getInstance().playSound(soundNames::HEAL);
			 
			 m_selection = std::nullopt;
		 }
		 else if (m_selection == QuitGame)
		 {
			 SoundTon::getInstance().playSound(soundNames::CLICK);
			 
			 m_selection = std::nullopt;
			
			 std::this_thread::sleep_for(std::chrono::seconds(1));
			 
			 setQuitGame();
		 }
		//if not null,switch case what to do
	 }
	 
	 void handleEvents(sf::Event event)
	 {
		 if (event.type == sf::Event::KeyPressed)
		 {
			 if (event.key.code == sf::Keyboard::Enter)
			 {
				 m_selection = m_hover;
			 }

			 if (event.key.code == sf::Keyboard::Down)
			 {
				 SoundTon::getInstance().playSound(soundNames::MENU);
				 
				 m_hover = ++m_hover;
			 }
			 
			 
			 if (event.key.code == sf::Keyboard::Up)
			 {
				 SoundTon::getInstance().playSound(soundNames::MENU);
				 
				 m_hover = --m_hover;
			 }
			 
			 if (event.key.code == sf::Keyboard::M ||
				 event.key.code == sf::Keyboard::Escape)
			 {
				 SoundTon::getInstance().playSound(soundNames::NM_CLICK);
				 setStatus(false);
			 }
		 }
	 }
	 
	 void draw(sf::RenderWindow& window)
	 {
		 for (auto& gui : m_menuSelection)
		 {
			 gui->draw(window);
		 }
	 }

private:
	bool m_saving {false};
	bool m_finish {false};
	
	std::array<std::unique_ptr<Gui>, PlayerMenuSize> m_menuSelection {};

	std::optional<PlayerMenuOptions> m_selection{ std::nullopt };
	std::optional<PlayerMenuOptions> m_hover{ Pokemons };
	
	saveManager& m_saveGame;

	std::shared_ptr<Player> m_player;

	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
	sf::Vector2f m_cameraCenter;
};
