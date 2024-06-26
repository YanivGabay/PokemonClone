#pragma once

#include <iostream>
#include "Resources.h"
#include "entity/Player.h"
#include "entity\Entity.h"
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
		std::unique_ptr<tson::Map> map = parser.parse(fs::path(mapFile));
		
		if (map->getStatus() != tson::ParseStatus::OK)
		{
			tson::ParseStatus status = map->getStatus();
			std::string errorMessage;

			switch (status)
			{
				case tson::ParseStatus::FileNotFound:
					errorMessage = "File not found";
					break;
				case tson::ParseStatus::ParseError:
					errorMessage = "Parse error";
					break;
				case tson::ParseStatus::MissingData:
					errorMessage = "Missing data";
					break;
				default:
					errorMessage = "Unknown error";
					break;
			}
			
			throw std::runtime_error("Error loading map");
			
			exit(5);
			return;
		}
		
		tson::Vector2i myvector = map.get()->getSize();
		
		m_mapXSize = myvector.x;
		m_mapYSize = myvector.y;

		tson::Tileset* tileset = map->getTileset("spritesheet");
		
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
						
						tson::Vector2f myPosition = tile->getPosition({i,j});
						sf::Vector2f actualPosition;
						
						actualPosition.x = myPosition.x;
						actualPosition.y = myPosition.y;
						
						std::string mytype = tile->getClassType();
						auto gameTile = std::make_unique<Tile>(mytype, mySprite, actualPosition);
						
						tson::Animation animations = tile->getAnimation();
						
						if (animations.any())
						{
							std::vector<sf::IntRect> animationsRects;
							
							for (int animation = 0; animation < animations.size(); animation++)
							{
								std::vector<tson::Frame> frames = animations.getFrames();
								
								uint32_t id = frames[animation].getTileId();
								
								//crashing here:
								tson::Rect currAnimRect = tileset->getTile(id)->getDrawingRect();
								
								sf::IntRect spriteRect(currAnimRect.x, currAnimRect.y, currAnimRect.width, currAnimRect.height);
								
								animationsRects.push_back(spriteRect);
							}
							
							gameTile->addAnimation(mytype, std::move(animationsRects),0.5f);
							
							if (!checkIfContinous(mytype))
							{
								gameTile->setAnimationMode(AnimationMode::SingleLoop);
							}
						}
						
						int id = layer.getId();
						
						if (id == static_cast<int>(LAYERS::LOWER))
						{
							m_lowerTiles.push_back(std::move(gameTile));
						}
						else if (id == static_cast<int>(LAYERS::MEDIUM))
						{
							m_mediumTiles.push_back(std::move(gameTile));

							m_mediumMap.emplace(std::make_pair(actualPosition.x, actualPosition.y), m_mediumTiles.back().get());
							
							if (mytype == "portal")
							{
								m_exits.push_back((m_mediumTiles.back().get()));
							}
						}
						else
						{
							m_upperTiles.push_back(std::move(gameTile));
							
							m_upperMap.emplace(std::make_pair(actualPosition.x, actualPosition.y), m_upperTiles.back().get());
						}
					}
				}
			}
		}
	}
	
	sf::Vector2i getExitBackPos()
	{
		sf::Vector2i m_pos;

		m_pos.x = m_exits.back()->getPosition().x / TILE_SIZE;
		m_pos.y = m_exits.back()->getPosition().y / TILE_SIZE;
		
		return m_pos;
	}
	
	sf::Vector2i getExitPos()
	{
		sf::Vector2i m_pos;
		
		m_pos.x = m_exits.front()->getPosition().x / TILE_SIZE ;
		m_pos.y = m_exits.front()->getPosition().y / TILE_SIZE ;
		
		return m_pos;
	}
	
	void draw(sf::RenderWindow& window)
	{
		for (auto& tile : m_lowerTiles)
		{
			tile->draw(window);
		}

		for (auto& tile : m_mediumTiles)
		{
			tile->draw(window);
		}

		for (auto& tile : m_upperTiles)
		{
			tile->draw(window);
		}
	}

	void updateAnimations(sf::Time dt)
	{
		for (auto& tile : m_mediumTiles)
		{
			if (tile->getAnimationStatus())
			{
				tile->updateAnimation(dt);
			}
		}
		
		for (auto& tile : m_upperTiles)
		{
			if (tile->getAnimationStatus())
			{
				tile->updateAnimation(dt);
			}
		}
	}
	
	bool checkCollisionUpper(sf::Vector2i target)
	{
		//if its equal, we didnt find so we return false
		return m_upperMap.find(std::make_pair(target.x, target.y)) != m_upperMap.end();
	}
	
	struct PairHash
	{
		template <class T1, class T2>
		std::size_t operator () (const std::pair<T1, T2>& p) const
		{
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);
			
			return h1 ^ h2; // or use a better combining function
		}
	};
	
	Tile* getTile(int x, int y)
	{
		auto iterator = m_mediumMap.find(std::make_pair(x * TILE_SIZE, y * TILE_SIZE));

		if (iterator != m_mediumMap.end())
		{
			// Tile exists at the specified coordinates
			return iterator->second;
		}

		// Tile does not exist
		return nullptr;
	}
	std::pair<int, int> getMapSize()
	{
		std::pair<int, int>x(m_mapXSize, m_mapYSize);

		return x;
	}

private:
	std::vector<std::unique_ptr<Tile>> m_lowerTiles;
	std::vector<std::unique_ptr<Tile>> m_mediumTiles;
	std::vector<std::unique_ptr<Tile>> m_upperTiles;

	std::vector<Tile*> m_exits;
	
	std::unordered_map<std::pair<int, int>, Tile*, PairHash> m_mediumMap;
	std::unordered_map<std::pair<int, int>, Tile*, PairHash> m_upperMap;

	int m_mapXSize;
	int m_mapYSize;
};
