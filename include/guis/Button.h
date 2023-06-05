#pragma once
#include "Resources.h"


class Button
{
public:
	Button(sf::Vector2f guiSize,sf::Vector2f position,sf::Texture texture):m_frameBoxRects(Resources::getInstance().getFrameCord()),
													m_size(guiSize), m_startPosition(position),m_texture(texture)
	{
		init();
	}
	void init()
	{
		auto sizeVector = sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2);


		auto middle = std::make_unique<sf::RectangleShape>(sizeVector);
		sf::IntRect rect = *m_frameBoxRects[MIDDLE];
		middle->setTexture(&m_texture);
		middle->setPosition(m_startPosition);
		m_shapes.push_back(std::move(middle));

		auto leftUpperCorner = std::make_unique<sf::RectangleShape>(sizeVector);
		 rect = *m_frameBoxRects[LEFT_UP_CORNER];
		leftUpperCorner->setTextureRect(rect);
		leftUpperCorner->setPosition(m_startPosition);
		m_shapes.push_back(std::move(leftUpperCorner));

		auto rightUpperCorner = std::make_unique<sf::RectangleShape>(sizeVector);
		 rect = *m_frameBoxRects[RIGHT_UP_CORNER];
		rightUpperCorner->setTextureRect(rect);
		rightUpperCorner->setPosition(m_startPosition.x+m_size.x,m_startPosition.y);
		m_shapes.push_back(std::move(rightUpperCorner));

		auto leftButtomCorner = std::make_unique<sf::RectangleShape>(sizeVector);
		 rect = *m_frameBoxRects[LEFT_DOWN_CORNER];
		leftButtomCorner->setTextureRect(rect);
		leftButtomCorner->setPosition(m_startPosition.x, m_startPosition.y+m_size.y);
		m_shapes.push_back(std::move(leftButtomCorner));

		auto rightButtomCorner = std::make_unique<sf::RectangleShape>(sizeVector);
		 rect = *m_frameBoxRects[RIGHT_DOWN_CORNER];
		rightButtomCorner->setTextureRect(rect);
		rightButtomCorner->setPosition(m_startPosition.x+m_size.x, m_startPosition.y + m_size.y);
		m_shapes.push_back(std::move(rightButtomCorner));
		//between left and right upper corner // horiz up

		for (size_t i = 1; i < m_size.x; i++)
		{
			auto horizUp = std::make_unique<sf::RectangleShape>(sizeVector);
			 rect = *m_frameBoxRects[UP_HORIZ];
			horizUp->setTextureRect(rect);
			horizUp->setPosition(m_startPosition.x + i* 8, m_startPosition.y );
			m_shapes.push_back(std::move(horizUp));

			auto horizDown = std::make_unique<sf::RectangleShape>(sizeVector);
			 rect = *m_frameBoxRects[DOWN_HORIZ];
			horizDown->setTextureRect(rect);
			horizDown->setPosition(m_startPosition.x + i * 8, m_startPosition.y+m_size.y);
			m_shapes.push_back(std::move(horizDown));
		}

		for (size_t i = 1; i < m_size.y; i++)
		{
			auto verticalLeft = std::make_unique<sf::RectangleShape>(sizeVector);
			 rect = *m_frameBoxRects[UP_HORIZ];
			verticalLeft->setTextureRect(rect);
			verticalLeft->setPosition(m_startPosition.x , m_startPosition.y+i*8);
			m_shapes.push_back(std::move(verticalLeft));

			auto verticalRight = std::make_unique<sf::RectangleShape>(sizeVector);
			 rect = *m_frameBoxRects[DOWN_HORIZ];
			verticalRight->setTextureRect(rect);
			verticalRight->setPosition(m_startPosition.x +m_size.x, m_startPosition.y + i * 8);
			m_shapes.push_back(std::move(verticalRight));
		}
		
		
	}
	~Button()
	{
	}
	void draw(sf::RenderWindow& window)
	{
		for (const auto& shape : m_shapes)
		{
			window.draw(*shape);
		}
	}

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::vector<std::unique_ptr<sf::RectangleShape>> m_shapes;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_size;
	std::unordered_map<FrameID, std::unique_ptr<sf::IntRect>>& m_frameBoxRects;
	
};
