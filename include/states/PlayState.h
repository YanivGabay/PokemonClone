#pragma once

#include "BaseState.h"
#include "world/TilesMap.h"
#include "Level.h"
#include "entity/Player.h"


class PlayState : public BaseState
{
public:
	PlayState(Stack<BaseState>& states)
		: BaseState(states),
		  m_camera(std::make_unique<Camera>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)),
		  m_player(std::make_unique<Player>()),
		  m_currentLevel(std::make_unique<Level>())
	{
		sf::Vector2f playerPixelPosition = gridToPixelPosition(m_player->getPosition());
		m_camera->update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);
	}
	
	~PlayState() = default;
	
	void entry() override {}
	void exit() override {}
	
	void update(sf::Time dt) override
	{
		m_player->update(dt);

		sf::Vector2i curr = m_player.get()->getPosition();

	
		 sf::Vector2f playerPixelPosition = gridToPixelPosition(m_player->getPosition());
		 m_camera->update(playerPixelPosition.x + TILE_SIZE / 2.0f, playerPixelPosition.y + TILE_SIZE / 2.0f);

		 m_currentLevel->updateAnimations(dt);
	 }
	
	void handleEvents(sf::Event event) override
	{
		m_player->handleInput();
	}
	
	void draw(sf::RenderWindow& window) override
	{
		m_currentLevel->draw(window);
		m_player->draw(window);
		window.setView(m_camera->getView());
	}

private:
	std::unique_ptr<Level> m_currentLevel;
	std::reference_wrapper<Stack<BaseState>> m_states{ getStateStack() };
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Camera> m_camera;
};
