#pragma once
#include "Resources.h"
#include "entity/Player.h"


class Tile
{
public:
	Tile(TileID id, sf::Sprite& mysprite, sf::Vector2f position) : m_myid(id), m_mySprite(mysprite), m_position(position)
	{
		if (m_mySprite.getTexture() == nullptr)
			std::cout << "tile got bad sprite" << std::endl;
		
		
	};

	~Tile()
	{
	};
	void draw(sf::RenderWindow& window)
	{
		m_mySprite.setPosition(m_position);
		
		if (m_mySprite.getTexture() == nullptr)
			std::cout << "Tile sprite has no texture!" << std::endl;
		else
			//std::cout << "Tile position: x=" << m_position.x << ", y=" << m_position.y << std::endl;
			window.draw(m_mySprite);
	}

private:

	enum TileID m_myid;
	 sf::Sprite& m_mySprite;
	sf::Vector2f m_position;

};
