#pragma once
#include "Resources.h"
#include "entity/Player.h"
class Tile
{
public:
	Tile(TileID id, sf::Sprite& mysprite, sf::Vector2f position) : m_myid(id), m_mySprite(mysprite), m_position(position)
	{
		m_mySprite.setPosition(m_position);
		
	};

	~Tile()
	{
	};
	void draw(sf::RenderWindow& window)
	{
		window.draw(m_mySprite);
	}
private:

	enum TileID m_myid;
	sf::Sprite& m_mySprite;
	sf::Vector2f m_position;

};
