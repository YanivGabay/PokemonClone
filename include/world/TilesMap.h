#pragma once
#include "Resources.h"
#include "entity/Player.h"
#include "Tile.h"

sf::Vector2f gridToPixelPosition(sf::Vector2i gridPosition)
{
	return sf::Vector2f(gridPosition.x * TILE_SIZE, gridPosition.y * TILE_SIZE);
}


class TilesMap
{
public:
	TilesMap() 
	{
		m_lowerTiles = initTiles(m_mapXSize, m_mapYSize);
	};

	~TilesMap()
	{
	};
	std::vector<std::unique_ptr<Tile>> initTiles(int mapXSize,int mapYSize)
	{
		Resources& resources = Resources::getInstance();
		std::vector < std::unique_ptr<Tile>> tiles;

		sf::Sprite& grass = resources.getTileSprite(GRASS);
		for (int j = 0; j < mapYSize; j++)
		{
			for (int i = 0; i < mapXSize; i++)
			{
				sf::Vector2f position(i * 16, SCREEN_HEIGHT - (j * 16));
				tiles.push_back(std::make_unique<Tile>(GRASS, grass, position));
				std::cout << "x:" << position.x << "y:" << position.y << std::endl;

			}
		}
		return tiles;
	}
	void draw(sf::RenderWindow& window)
	{
		for (auto& tile	: m_lowerTiles)
		{
			tile->draw(window);
		
			
			
		}
		window.display();
		sf::sleep(sf::Time(sf::seconds(0.025)));
	}
private:
	std::vector<std::unique_ptr<Tile>> m_lowerTiles;
	std::vector<std::unique_ptr<Tile>> m_mediumTiles;
	std::vector<std::unique_ptr<Tile>> m_upperTiles;

	const int m_mapXSize = 30;
	const int m_mapYSize = 30;
};
