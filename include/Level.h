#pragma once

#include "world/TilesMap.h"
#include "utilities.h"



class Level
{
public:
	using MapIterator = std::vector<std::unique_ptr<TilesMap>>::iterator;
	Level()
	{
		m_maps.emplace_back(std::make_unique<TilesMap>("resources/firstTown.tmj"));
		m_maps.emplace_back(std::make_unique<TilesMap>("resources/secondMap.tmj"));
			m_currLevel = m_maps.begin();
			
	}
	

	
	
	~Level() = default;
	
	void draw(sf::RenderWindow& window)
	{
		(*m_currLevel)->draw(window);
	}
	
	void updateAnimations(sf::Time dt)
	{
		(*m_currLevel)->updateAnimations(dt);
	}

	Tile* getActiveTile(int x,int y)
	{
		return (*m_currLevel)->getTile(x, y);
	}
	bool checkCollisionUpper(sf::Vector2i target)
	{
		return (*m_currLevel)->checkCollisionUpper(target);
	}
	const int getEncounterRate()
	{
		return m_encounterRate;
	}
	const LevelID getLevelId()
	{
		return m_id;
	}
	void nextLevel()
	{
		m_currLevel++;
		m_id = static_cast<LevelID>(static_cast<int>(LevelID::START_TOWN) + 1);
	}
	void returnLevel()
	{
		m_currLevel--;
		m_id = static_cast<LevelID>(static_cast<int>(LevelID::START_TOWN) -1);
	}
private:
	
	std::vector<std::unique_ptr<TilesMap>> m_maps;
	
	MapIterator m_currLevel;
	LevelID m_id{ LevelID::START_TOWN };
	int m_encounterRate{ 2 };
};
