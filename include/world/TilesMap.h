#pragma once

#include "Resources.h"
#include "entity/Player.h"
#include "../Tile.h"
#include "tileson/tileson.hpp"

class TilesMap
{
public:
	TilesMap(const std::string mapFile) 
		
	{
		loadLevel(mapFile);
	}

	~TilesMap() = default;

	//this is an example of a specfic function that will init a single map
	//need to make it more generic,or make a bank of maps
	void loadLevel(const std::string& mapFile)
	{
		sf::Texture& spriteSheet = Resources::getInstance().getTexture("spritesheet.png");
		tson::Tileson parser;
		std::unique_ptr<tson::Map> map = parser.parse(mapFile);
		if (!map)
		{
			std::cout << "ERRORLOADINGMAP" << std::endl;
			return;
		}

		m_mapXSize = map.get()->getSize().x;
		m_mapYSize = map.get()->getSize().y;

		
			for (auto& layer : map->getLayers())
			{
				std::map<std::tuple<int, int>, tson::Tile*> tileData = layer.getTileData();
				int x = layer.getSize().x;
				int y = layer.getSize().y;
					//Must check for nullptr, due to how we got the first invalid tile (pos: 0, 4)
					//Would be unnecessary otherwise.
				for (int i = 0; i < x; i++)
				{
					for (int j = 0; j < y; j++)
					{
						tson::Tile* tile = layer.getTileData(i,j);
						if (tile != nullptr)
						{

							tson::Rect currRect = tile->getDrawingRect();
							sf::IntRect myRect(currRect.x, currRect.y, currRect.width, currRect.height);
							sf::Sprite mySprite(spriteSheet, myRect);

							tson::Vector2i myPosition = tile->getPositionInTileUnits({i,j});
							std::string mytype = tile->getClassType();

							int id = layer.getId();
							if (id == 1)
							{
								m_lowerTiles.push_back(std::move(std::make_unique<Tile>(mytype, mySprite, myPosition)));
							}
							else if (id == 2)
							{
								m_mediumTiles.push_back(std::move(std::make_unique<Tile>(mytype, mySprite, myPosition)));
							}
							else
							{
								m_upperTiles.push_back(std::move(std::make_unique<Tile>(mytype, mySprite, myPosition)));
							}



						}
					}
				}
					
						
				
			}
		

	}


	void draw(sf::RenderWindow& window)
	{
		for (auto& tile	: m_lowerTiles)
			tile->draw(window);

		for (auto& tile : m_mediumTiles)
			tile->draw(window);

		for (auto& tile : m_upperTiles)
			tile->draw(window);
	}

private:
	std::vector<std::unique_ptr<Tile>> m_lowerTiles;
	std::vector<std::unique_ptr<Tile>> m_mediumTiles;
	std::vector<std::unique_ptr<Tile>> m_upperTiles;
	std::vector<std::unique_ptr<Tile>> m_exits;
	
	int m_mapXSize;
	int m_mapYSize;
};
