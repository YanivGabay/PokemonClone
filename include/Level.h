#pragma once

#include "world/TilesMap.h"
#include "utilities.h"


class Level
{
public:
	Level()
		: m_map(std::make_unique<TilesMap>("resources/firstTown.tmj")) {}
	
	~Level() = default;
	
	void draw(sf::RenderWindow& window)
	{
		m_map->draw(window);
	}
	
	void updateAnimations(sf::Time dt)
	{
		m_map->updateAnimations(dt);
	}
	void activeTile()
	{
		m_map->activeAnim();
	}
	bool checkCollisionUpper(sf::Vector2i target)
	{
		return m_map->checkCollisionUpper(target);
	}
private:
	std::unique_ptr<TilesMap> m_map;
	LevelID m_id{ LevelID::START_TOWN };
};
