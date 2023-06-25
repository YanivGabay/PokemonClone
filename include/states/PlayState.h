#pragma once

#include "BaseState.h"
#include "world/TilesMap.h"
#include "Level.h"
#include "entity/Player.h"
#include "entity\Entity.h"
#include "entity\NPC.h"
#include <random>
#include "Pokemon/PokemonFactory.h"
#include "EncounterBattleState.h"
#include "SoundTon.h"
#include "TransitionState.h"

class PlayState : public BaseState
{
public:
	PlayState(Stack<BaseState>& states)
		: BaseState(states),
		  m_camera(std::make_unique<Camera>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)),
		  m_player(std::make_shared<Player>()),
		  m_NPC(std::make_shared<NPC>()),
		  m_currentLevel(std::make_unique<Level>()),
		  m_pokemonFactory(std::make_unique<PokemonFactory>())
	{
		
		sf::Vector2f playerPixelPosition = gridToPixelPosition(m_player->getPosition());
		m_camera->update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);

		//temporary
		std::cout << "before add pokemon in playstate" << std::endl;
		std::shared_ptr<Pokemon> firstpokemon = m_pokemonFactory->createPokemon(PokemonIndex::CHARIZARD);
		m_player->addPokemon(firstpokemon);

		SoundTon::getInstance().stopSound(soundNames::OPEN);
		
		SoundTon::getInstance().playSound(soundNames::CITY);
	}
	
	~PlayState() = default;
	
	void entry() override {
		getStateStack().get().popStart();
		m_NPC->setMovable(false);
	}

	void exit() override {}
	
	std::array<sf::Vector2i, SIDES> getOptions(sf::Vector2i position)
	{
		std::array<sf::Vector2i, SIDES> neighbors {};
		neighbors[RIGHT] = sf::Vector2i(position.x + 1, position.y);
		neighbors[UP] = sf::Vector2i(position.x , position.y-1);
		neighbors[DOWN] = sf::Vector2i(position.x , position.y+1);
		neighbors[LEFT] = sf::Vector2i(position.x-1 , position.y);

		return neighbors;
	}
	
	const std::map<Side, bool> getMovesMap(sf::Vector2i currPos)
	{
		

		std::array<sf::Vector2i, SIDES> tilesOptions = getOptions(currPos);
		std::map <Side, bool> directionMap;
		directionMap[RIGHT] = m_currentLevel->checkCollisionUpper(tilesOptions[RIGHT] * TILE_SIZE);
		directionMap[LEFT] = m_currentLevel->checkCollisionUpper(tilesOptions[LEFT] * TILE_SIZE);
		directionMap[UP] = m_currentLevel->checkCollisionUpper(tilesOptions[UP] * TILE_SIZE);
		directionMap[DOWN] = m_currentLevel->checkCollisionUpper(tilesOptions[DOWN] * TILE_SIZE);

		return directionMap;
	}
	void checkTileOn(sf::Vector2i updatedPos)
	{
		Tile* tile = m_currentLevel->getActiveTile(updatedPos.x, updatedPos.y);
		if (tile)
		{
			std::string type = tile->getId();

			if (type == "tallgrass"&&m_player->getIsMoving())
			{
				tile->playAnimation(sf::Time(sf::seconds(1.0f / 60.0f)));

				if (m_currentLevel->getEncounterRate() > generateRandomNumber(0, 100))
				{
					// SoundTon::getInstance().playSound(soundNames::BUSH);
					triggerBattleEncounter(m_currentLevel->getLevelId());
				}
			}
			else if (type == "portal")
			{
			
				
				auto fadeout = std::make_unique<FadeOutState>(getStateStack().get(), sf::Color::White,true);
																
				getStateStack().get().pushQueueState(std::move(fadeout));
				m_transition = true;
			}
			else
			{
				;
			}
		}
	}
	
	
	void resetBeforeBattle()
	{
		m_player->setMoving(false);
	}
	void triggerBattleEncounter(LevelID levelId)
	{
		std::cout << "battle should trigger" << std::endl;
		resetBeforeBattle();
		std::shared_ptr<Pokemon> wildPokemon = m_pokemonFactory->createRandomPokemon(levelId);
		
		auto encounterBattle = std::make_unique<EncounterBattleState>(getStateStack().get(), m_player, wildPokemon);
		
		auto transition = std::make_unique<TransitionState>(getStateStack().get(), std::move(encounterBattle), Resources::getInstance().getColor(BLACK));
		
		getStateStack().get().pushQueueState(std::move(transition));
	}

	void update(sf::Time dt) override
	{
		if (m_transition)
		{
			if (m_player->getPosition().y < 300)
				m_currentLevel->nextLevel();
			else
				m_currentLevel->returnLevel();

			auto fadein = std::make_unique<FadeInState>(getStateStack().get(), sf::Color::White);
			getStateStack().get().pushQueueState(std::move(fadein));
			m_transition = false;
		}
		static bool firstUpdate = false;
		if (!firstUpdate)
		{
			entry();
			firstUpdate = true;
		}
		
		checkCollision(dt);
		checkTileOn(m_player->getPosition());
		//if on grass rool a dice
		// if certain push battlestate and other states
		
		// test to check play animation
		sf::Vector2f playerPixelPosition = gridToPixelPosition(m_player->getPosition());
		m_camera->update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);
		
		m_currentLevel->updateAnimations(dt);
	}
	
	void checkCollision(sf::Time dt)
	{
		m_player->update(dt, getMovesMap(m_player->getPosition()));
		m_NPC->update(dt, getMovesMap(m_NPC->getPosition()));

		//if we are here, the player is after collision check

		
	}
	
	
	void handleEvents(sf::Event event) override
	{
		m_player->handleInput();
		
	}
	
	void draw(sf::RenderWindow& window) override
	{
		m_currentLevel->draw(window);
		m_player->draw(window);
		m_NPC->draw(window);
		window.setView(m_camera->getView());
	}

private:
	bool m_transition {false};

	std::unique_ptr<Level> m_currentLevel;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<NPC> m_NPC;
	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<PokemonFactory> m_pokemonFactory;
};
