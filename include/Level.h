#pragma once
#include "world/TilesMap.h"
#include "utilities.h"
class Level 
{
public:
	Level() : m_map(std::make_unique<TilesMap>("resources/firstTown.tmj"))
	{
	}

	~Level()
	{
	}
	void draw(sf::RenderWindow& window)
	{
		m_map->draw(window);
	}
	void updateAnimations(float dt)
	{
		m_map->updateAnimations(dt);
	}
private:
	std::unique_ptr<TilesMap> m_map;
	LevelID m_id{ LevelID::START_TOWN };
};

