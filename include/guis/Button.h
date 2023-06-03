#pragma once
#include "Resources.h"
#include "Gui.h"

class Button
{
public:
	Button(sf::Vector2f size,sf::Vector2f position,sf::Texture texture):m_frameBoxRects(Resources::getInstance().getFrameCord()),
													m_size(size), m_startPosition(position),m_texture(texture)
	{
		init();
	}
	void init()
	{
		auto shape = std::make_unique<sf::RectangleShape>(m_size);
		shape->setTexture(&m_texture);
		shape->setPosition(m_startPosition);

		sf::IntRect rect = *m_frameBoxRects[LEFT_UP_CORNER];
		shape->setTextureRect(rect);
		m_shapes.push_back(std::move(shape));

		for (size_t i = 0; i < m_size.x-1; i++)
		{
			shape->setPosition(m_startPosition.x * i*TILE_SIZE/2, m_startPosition.y);
			 rect = *m_frameBoxRects[UP_HORIZ];
			shape->setTextureRect(rect);
			m_shapes.push_back(std::move(shape));
		}
		rect = *m_frameBoxRects[RIGHT_UP_CORNER];
		shape->setTextureRect(rect);
		m_shapes.push_back(std::move(shape));

		for (size_t i = 0; i < m_size.y-1; i++)
		{

		}
		for (size_t i = 0; i < length; i++)
		{

		}
	}
	~Button()
	{
	}

private:
	sf::Texture m_texture;
	std::vector<std::unique_ptr<sf::RectangleShape>> m_shapes;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_size;
	std::unordered_map<FrameID, std::unique_ptr<sf::IntRect>>& m_frameBoxRects;
	
};
