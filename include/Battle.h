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
	Battle(Pokemon& playerPokemon,Pokemon& enemyPokemon)
		: m_playerPokemon(playerPokemon),
		  m_enemyPokemon(enemyPokemon)
	{
		sf::Texture& texture = Resources::getInstance().getTexture("resources/battlegroundSprites.png");
		m_backGround.setTexture(texture);
		m_backGround.setTextureRect(m_battlePosition);
		float scaleX = static_cast<float>(m_windowSize.x) / m_backGround.getTextureRect().width;
		float scaleY = 450.0f / m_backGround.getTextureRect().height;

		// Set the scale
		m_backGround.setScale(scaleX, scaleY);
		//m_backGround.setPosition(sf::Vector2f(0, 0));
		//float scaleX = static_cast<float>(m_windowSize.x) / texture.getSize().x;
		//float scaleY = static_cast<float>(m_windowSize.y) / texture.getSize().y;
	//	m_backGround.setScale(scaleX, scaleY);
		

		
	
		m_playerPokemonInfo = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(),sf::Vector2f(250,100),sf::Vector2f(SCREEN_WIDTH-350,SCREEN_HEIGHT-270)));

		m_enemyPokemonInfo = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(), sf::Vector2f(250, 100), sf::Vector2f(SCREEN_WIDTH-750,SCREEN_HEIGHT-520)));

		m_adviceActionInfo = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(), sf::Vector2f(800, 150), sf::Vector2f(0,452.0f )));
		
		


	};
	~Battle() {};
	
	void draw(sf::RenderWindow& window)
	{
		
		window.clear(sf::Color::White);
		window.draw(m_backGround);
		m_playerPokemonInfo->draw(window);
		m_enemyPokemonInfo->draw(window);
		m_adviceActionInfo->draw(window);
		
	}
private:
	sf::IntRect m_battlePosition{ 249,6,240,112 };

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

