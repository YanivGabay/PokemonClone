#pragma once
#include "world/TilesMap.h"

class Level 
{
public:
	Level() : m_map(std::make_unique<TilesMap>())
	{
	}

	~Level()
	{
	}
	void draw(sf::RenderWindow& window)
	{
		m_map->draw(window);
	}
private:
	std::unique_ptr<TilesMap> m_map;
	LevelID m_id;
};

