#pragma once

#include <thread> 

#include "Resources.h"
#include "guis/Gui.h"
#include "Pokemon/Pokemon.h"
#include "SoundTon.h"
#include "utilities.h"
#include "entity/Player.h"

enum class SpritesElements
{
	Background,
	PlayerPokemon,
	EnemyPokemon
};

class Battle
{
public:
	Battle(std::shared_ptr<Player> player, std::shared_ptr<Pokemon> enemyPokemon)
		: m_player(player),
		  m_enemyPokemon(enemyPokemon)
	{
		SoundTon::getInstance().stopSound(soundNames::CITY);
		SoundTon::getInstance().playSound(soundNames::BATTLE);
		
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
		
		m_playerPokemonInfo = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(),
			sf::Vector2f(250,100),sf::Vector2f(SCREEN_WIDTH-350,SCREEN_HEIGHT-270)));

		m_enemyPokemonInfo = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(),
			sf::Vector2f(250, 100), sf::Vector2f(SCREEN_WIDTH-750,SCREEN_HEIGHT-520)));

		m_adviceActionInfo = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(),
			sf::Vector2f(800, 150), sf::Vector2f(0,452.0f )));
		

		
		setGuis();

		std::cout << "after add progress bar" << std::endl;
		m_playerBackPokemon.setPosition(m_playerPokemonPos);
		m_enemyFrontPokemon.setPosition(m_enemyPokemonPos);   /// ---- writing error ----

	};
	
	~Battle()
	{
		SoundTon::getInstance().stopSound(soundNames::BATTLE);
		SoundTon::getInstance().playSound(soundNames::CITY);
	}
	
	void setGuis()
	{
		m_playerPokemonInfo->addProgressBar(m_playerPokemonInfo->getPosition().x ,
											m_playerPokemonInfo->getPosition().y + 40, m_playerPokemonInfo->getSize().x / 3, m_playerPokemonInfo->getSize().y / 6,
											sf::Color::Black, sf::Color::Green, m_player->getPokemon(0).getHpPercent());
		m_playerPokemonInfo->setText(PokemonNames.at(m_player->getPokemon(0).getName()));
		// need to check here if we dont get the map.end
		m_playerPokemonInfo->setResetColor();

		m_enemyPokemonInfo->addProgressBar(m_enemyPokemonInfo->getPosition().x ,
										   m_enemyPokemonInfo->getPosition().y + 40, m_enemyPokemonInfo->getSize().x / 3, m_enemyPokemonInfo->getSize().y / 6,
											sf::Color::Black, sf::Color::Green, m_enemyPokemon->getHpPercent());
		m_enemyPokemonInfo->setText(PokemonNames.at(m_enemyPokemon->getName()));
		// need to check here if we dont get the map.end
		m_enemyPokemonInfo->setResetColor();
	}
	void draw(sf::RenderWindow& window)
	{
		
		window.clear(sf::Color::White);
		window.draw(m_backGround);
		m_playerPokemonInfo->draw(window);
		m_enemyPokemonInfo->draw(window);
		m_adviceActionInfo->draw(window);
		window.draw(m_playerBackPokemon);
		window.draw(m_enemyFrontPokemon);
		
	}
private:
	sf::IntRect m_battlePosition{ 249,6,240,112 };

	sf::Sprite m_backGround;

	std::shared_ptr<Player> m_player;
	std::shared_ptr<Pokemon> m_enemyPokemon;

	sf::Sprite& m_playerBackPokemon {m_player->getPokemon(0).getBackSprite()};
	sf::Sprite& m_enemyFrontPokemon {m_enemyPokemon->getFrontSprite()};

	std::unique_ptr<Gui> m_playerPokemonInfo;
	std::unique_ptr<Gui> m_enemyPokemonInfo;
	std::unique_ptr<Gui> m_adviceActionInfo;

	const sf::Vector2u m_windowSize{ Resources::getInstance().getWindow().getSize() };
	
	sf::Vector2f m_playerPokemonPos {100,295};
	sf::Vector2f m_enemyPokemonPos {500,100};

};

