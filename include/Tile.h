#pragma once

#include "Resources.h"
#include "entity/Player.h"
#include "Animation.h"


const sf::Time TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);


class Tile
{
public:
	Tile (std::string id, sf::Sprite mysprite, sf::Vector2f position)
		: m_myid(id),
		  m_mySprite(mysprite),
		  m_position(position)
	{
		if (!m_mySprite.getTexture()) {
			std::cerr << "tile got bad sprite" << std::endl;
			throw std::runtime_error("Failed to load sprite.");
		}
	}
	
	~Tile() = default;
	
	void draw(sf::RenderWindow& window)
	{
		m_mySprite.setPosition(m_position);
		
		if (!m_mySprite.getTexture())
		{
			std::cerr << "Tile sprite has no texture!" << std::endl;
			throw std::runtime_error("Failed! Tile sprite has no texture.");
		}
		else
		{
			updateAnimation(TIME_PER_FRAME);
			window.draw(m_mySprite);
		}
	}
	
	void updateAnimation(sf::Time dt)
	{
		m_animation.playAnimation(m_myid, dt, m_mySprite);
	}
	
	void addAnimation(std::string animationType, const std::vector<sf::IntRect>& frames, float duration)
	{
		m_animation.addSequence(animationType, frames, duration);
	}

private:
	std::string m_myid;
	sf::Sprite m_mySprite;
	sf::Vector2f m_position;

	Animation<std::string> m_animation;
};
