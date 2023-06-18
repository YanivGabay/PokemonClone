#pragma once

#include "Resources.h"
#include "guis/Gui.h"

/*
enum class SpritesElements
{
	Background,
	PlayerPokemon,
	EnemyPokemon
};

class Battle
{
public:
	Battle(Pokemon& playerPokemon,Pokemon& enemyPokemon):
		m_playerPokemon(playerPokemon),m_enemyPokemon(enemyPokemon)
	{

		m_backGround.setScale(
			static_cast<float>(m_windowSize.x) / m_backGround.getTexture()->getSize().x,
			static_cast<float>(m_windowSize.y)*0.75 / m_backGround.getTexture()->getSize().y);
		m_enemyPokemon();
		m_playerPokemonInfo();
		m_adviceActionInfo();
	};
	~Battle() {};

private:
	sf::Sprite& m_backGround;
	Pokemon& m_playerPokemon;
	Pokemon& m_enemyPokemon;

	Gui m_playerPokemonInfo;
	Gui m_enemyPokemonInfo;
	Gui m_adviceActionInfo;
	const sf::Vector2u m_windowSize{ Resources::getInstance().getWindow().getSize() };

};

*/