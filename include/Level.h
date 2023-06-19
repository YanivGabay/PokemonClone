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

	Tile* getActiveTile(int x,int y)
	{
		return m_map->getTile(x, y);
	}
	bool checkCollisionUpper(sf::Vector2i target)
	{
		return m_map->checkCollisionUpper(target);
	}
	const int getEncounterRate()
	{
		return m_encounterRate;
	}
	const LevelID getLevelId()
	{
		return m_id;
	}
private:
	std::unique_ptr<TilesMap> m_map;
	LevelID m_id{ LevelID::START_TOWN };
	int m_encounterRate{ 2 };
};
