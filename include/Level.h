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
		m_maps.emplace_back(std::make_unique<TilesMap>("resources/thirdMap.tmj"));
		m_maps.emplace_back(std::make_unique<TilesMap>("resources/fourthMap.tmj"));
		m_currMap = m_maps.begin();
	}
	
	~Level() = default;
	
	void draw(sf::RenderWindow& window)
	{
		(*m_currMap)->draw(window);
	}
	
	void updateAnimations(sf::Time dt)
	{
		(*m_currMap)->updateAnimations(dt);
	}
	
	sf::Vector2i getBackExit()
	{
		return (*m_currMap)->getExitBackPos();
	}
	
	sf::Vector2i getExit()
	{
		return (*m_currMap)->getExitPos();
	}
	
	Tile* getActiveTile(int x,int y)
	{
		return (*m_currMap)->getTile(x, y);
	}
	
	bool checkCollisionUpper(sf::Vector2i target)
	{
		return (*m_currMap)->checkCollisionUpper(target);
	}

	const std::pair<int,int> getMapSize()
	{
		return m_currMap->get()->getMapSize();
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
		if (m_currMap != m_maps.end() - 1)
		{
			m_currMap++;
			m_id = static_cast<LevelID>(static_cast<int>(m_id) + 1);
		}
	}
	
	void returnLevel()
	{
		if (m_currMap != m_maps.begin())
		{
			m_currMap--;
			m_id = static_cast<LevelID>(static_cast<int>(m_id) - 1);
		}
	}
	
	void setEncounterRate(int rate)
	{
		m_encounterRate = rate;
	}
	
	void setLevelId(LevelID id)
	{
		m_id = id;
	}

	void resetMap()
	{
		m_currMap = m_maps.begin();

		for (size_t i = 0; i < size_t(m_id); i++)
		{
			if (m_currMap != m_maps.end() - 1)
			{
				m_currMap++;
			}
		}
	}

private:
	std::vector<std::unique_ptr<TilesMap>> m_maps;
	
	MapIterator m_currMap;
	LevelID m_id{ LevelID::START_TOWN };
	
	int m_encounterRate{ 2 };
};
