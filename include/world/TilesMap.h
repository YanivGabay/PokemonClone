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
		sf::Texture& spriteSheet = Resources::getInstance().getTexture("resources/spritesheet.png");
		tson::Tileson parser;
		std::unique_ptr<tson::Map> map = parser.parse(mapFile);
		if (!map)
		{
			std::cout << "ERRORLOADINGMAP" << std::endl;
			exit(5);
			return;
		}
		
		m_mapXSize = map.get()->getSize().x;
		m_mapYSize = map.get()->getSize().y;

		tson::Tileset* tileset = map->getTileset("mysheet");
		
			for (auto& layer : map->getLayers())
			{
				std::map<std::tuple<int, int>, tson::Tile*> tileData = layer.getTileData();
				int x = layer.getSize().x;
				int y = layer.getSize().y;
				std::cout << "y: " << y << std::endl;
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
							sf::Vector2f actualPosition;
							actualPosition.x = myPosition.x;
							actualPosition.y = myPosition.y;


							std::string mytype = tile->getClassType();
							std::cout << "my type is: " << mytype << std::endl;
							auto gameTile = std::make_unique<Tile>(mytype, mySprite, actualPosition);

							tson::Animation animations = tile->getAnimation();
							if (animations.any())
							{
								std::vector<sf::IntRect> animationsRects;
								for (int i = 0; i < animations.size(); i++)
								{
									std::vector<tson::Frame> frames = animations.getFrames();
									uint32_t id = frames[i].getTileId();
									tson::Rect currAnimRect = tileset->getTile(id)->getDrawingRect();
									sf::IntRect spriteRect(currRect.x, currRect.y, currRect.width, currRect.height);
									animationsRects.push_back(spriteRect);
									
								}
								gameTile->addAnimation(mytype, std::move(animationsRects), 1.0f);
							}
							
							
							int id = layer.getId();
							if (id == static_cast<int>(LAYERS::LOWER))
							{
								m_lowerTiles.push_back(std::move(gameTile));
							}
							else if (id == static_cast<int>(LAYERS::MEDIUM))
							{
								m_mediumTiles.push_back(std::move(gameTile));
							}
							else
							{
								m_upperTiles.push_back(std::move(gameTile));
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
	void updateAnimations(float dt)
	{
		for (auto& tile : m_lowerTiles)
			tile->updateAnimation(dt);

		for (auto& tile : m_mediumTiles)
			tile->updateAnimation(dt);

		for (auto& tile : m_upperTiles)
			tile->updateAnimation(dt);
	}
private:
	std::vector<std::unique_ptr<Tile>> m_lowerTiles;
	std::vector<std::unique_ptr<Tile>> m_mediumTiles;
	std::vector<std::unique_ptr<Tile>> m_upperTiles;
	std::vector<std::unique_ptr<Tile>> m_exits;
	
	int m_mapXSize;
	int m_mapYSize;
};
