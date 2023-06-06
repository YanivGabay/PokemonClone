#pragma once

#include "Resources.h"
#include "entity/Player.h"


class Tile
{
public:
	Tile(MapID id, sf::Sprite& mysprite, sf::Vector2f position)
		: m_myid(id), m_mySprite(mysprite), m_position(position)
	{
		if (!m_mySprite.getTexture()) {
			std::cout << "tile got bad sprite" << std::endl;
			throw std::runtime_error("Failed to load sprite.");
		}
	};

	~Tile() = default;

	void draw(sf::RenderWindow& window)
	{
		m_mySprite.setPosition(m_position);
		
		if (!m_mySprite.getTexture()) {
			std::cout << "Tile sprite has no texture!" << std::endl;
			throw std::runtime_error("Failed! Tile sprite has no texture.");
		}
		else
			window.draw(m_mySprite);
	}

private:
	MapID m_myid;
	sf::Sprite& m_mySprite;
	sf::Vector2f m_position;
};
