#pragma once

#include "Resources.h"
#include "guis/Gui.h"
#include "Pokemon/Pokemon.h"

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
			static_cast<float>(m_windowSize.y)*0.75 / m_backGround.getTexture()->getSize().y
			
		);
		sf::Font& font = Resources::getInstance().getFont();
		m_playerPokemonInfo = std::move(std::make_unique<Gui>(font,sf::Vector2f(200,200),sf::Vector2f(m_backGround.getPosition().x+500,m_backGround.getPosition().y+100)));

		m_enemyPokemonInfo = std::move(std::make_unique<Gui>(font, sf::Vector2f(200, 200), sf::Vector2f(m_backGround.getPosition().x + 50, m_backGround.getPosition().y-500)));

		m_adviceActionInfo = std::move(std::make_unique<Gui>(font, sf::Vector2f(200, 200), sf::Vector2f(m_backGround.getPosition().x + 50, m_backGround.getPosition().y)));
		
		sf::Texture& texture = Resources::getInstance().getTexture("resources/battlegroundSprites.png");
		m_backGround.setTexture(texture);
		m_backGround.setTextureRect(m_battlePosition);


	};
	~Battle() {};
	
	void draw(sf::RenderWindow& window)
	{
		window.draw(m_backGround);
		m_playerPokemonInfo->draw(window);
		m_enemyPokemonInfo->draw(window);
		m_adviceActionInfo->draw(window);
		
	}
private:
	sf::IntRect m_battlePosition{ 249,6,241,112 };

	sf::Sprite m_backGround;
	Pokemon& m_playerPokemon;
	Pokemon& m_enemyPokemon;


	std::unique_ptr<Gui> m_playerPokemonInfo;
	std::unique_ptr<Gui> m_enemyPokemonInfo;
	std::unique_ptr<Gui> m_adviceActionInfo;
	const sf::Vector2u m_windowSize{ Resources::getInstance().getWindow().getSize() };
	
	//sf::Vector2i m_playerPokemon;
	//sf::Vector2i m_enemyPokemon;

};

