#pragma once

#include "Resources.h"
#include "entity/Player.h"
#include "../Tile.h"





class TilesMap
{
public:
	TilesMap()
		: m_mapXSize(30),m_mapYSize(30), m_lowerTiles(initTiles(30, 30,GRASS)/*Regular tiles*/), m_mediumTiles(initTiles(15, 15, TALLGRASS)/*Tall Grass*/)
	{}

	~TilesMap() = default;

	//this is an example of a specfic function that will init a single map
	//need to make it more generic,or make a bank of maps
	std::vector<std::unique_ptr<Tile>> initTiles(int mapXSize,int mapYSize,TileID tileType)
	{
		Resources& resources = Resources::getInstance();
		std::vector < std::unique_ptr<Tile>> tiles;
		
		for (int j = 0; j < mapYSize; j++)
		{
			for (int i = 0; i < mapXSize; i++)
			{
				sf::Vector2f position(i * TILE_SIZE, (j * TILE_SIZE));
				tiles.push_back(std::make_unique<Tile>(tileType, resources.getTileSprite(tileType), position));
				// std::cout << "x:" << position.x << "y:" << position.y << std::endl;
			}
		}

		return tiles;
	}

	void draw(sf::RenderWindow& window)
	{
		for (auto& tile	: m_lowerTiles)
			tile->draw(window);

		for (auto& tile : m_mediumTiles)
			tile->draw(window);
	}

private:
	std::vector<std::unique_ptr<Tile>> m_lowerTiles;
	std::vector<std::unique_ptr<Tile>> m_mediumTiles;
	std::vector<std::unique_ptr<Tile>> m_upperTiles;
 
	int m_mapXSize;
	int m_mapYSize;
};
