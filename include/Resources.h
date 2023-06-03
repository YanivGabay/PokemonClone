#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <array>

#include "utilities.h"
enum FrameID
{
	LEFT_UP_CORNER,  
	UP_HORIZ,
	RIGHT_UP_CORNER,
	LEFT_VERTICAL,
	MIDDLE,
	RIGHT_VERTICAL,
	LEFT_DOWN_CORNER,
	DOWN_HORIZ,
	RIGHT_DOWN_CORNER
	
};
enum Colors
{
	RED,
	BLUE,
	BLACK,
	WHITE
};

class Resources
{
public:
	static Resources& getInstance()
	{
		static Resources instance;
		return instance;
	}
	sf::Color getColor(Colors color)
	{
		static std::unordered_map<Colors, sf::Color> colorMap = {
			{Colors::RED, sf::Color::Red},
			{Colors::BLUE, sf::Color::Blue},
			{Colors::BLACK, sf::Color::Black},
			{Colors::WHITE, sf::Color::White}
		};
		

		return colorMap[color];
	}
	sf::Texture& getTexture(const std::string& filename)
	{
		if (m_textures.find(filename) == m_textures.end())
		{
			m_textures[filename] = std::make_unique<sf::Texture>();
			if (!m_textures[filename]->loadFromFile(filename))
			{
				std::cerr << "Failed to load texture: " << filename << std::endl;
				throw std::runtime_error("Failed to load texture.");
			}
		}
		
		return *m_textures[filename];
	}
	
	sf::Font& getFont()
	{
		if (!m_font)
		{
			std::cerr << "Font has not been loaded." << std::endl;
			throw std::runtime_error("Font has not been loaded.");
		}

		return *m_font;
	}
	void loadFrames()
	{
		
		sf::Vector2i size = sf::Vector2i(TILE_SIZE/2, TILE_SIZE / 2);
		sf::Vector2i position = sf::Vector2i(0, 0);
		loadFont("Pokemon.FON");
		
		for (FrameID id = LEFT_UP_CORNER; id <= RIGHT_DOWN_CORNER; id = static_cast<FrameID>(static_cast<int>(id) + 1))
		{
			int row = static_cast<int>(id) / 3;  // Calculate the row index
			int col = static_cast<int>(id) % 3;  // Calculate the column index

			position.x = col * (TILE_SIZE / 2);   // Update the x position
			position.y = row * (TILE_SIZE / 2);   // Update the y position

			m_frameBoxRects[id] = std::make_unique<sf::IntRect>(position.x,position.y, size.x,size.y);
		}

	}
	sf::Sprite& getTileSprite(TileID tileId)
	{
		if (m_tileSprites.find(tileId) == m_tileSprites.end())
		{
			std::cerr << "Tile sprite not found: " << tileId << std::endl;
			throw std::runtime_error("Tile sprite not found.");
		}

		return *m_tileSprites[tileId];
	}

	void loadFont(const std::string& filename)
	{
		if (m_font)
		{
			std::cerr << "Font has already been loaded." << std::endl;
			throw std::runtime_error("Font has already been loaded.");
		}
		
		m_font = std::make_unique<sf::Font>();
		
		if (!m_font->loadFromFile(filename))
		{
			std::cerr << "Failed to load font: " << filename << std::endl;
			throw std::runtime_error("Failed to load font.");
		}
	}
	std::unordered_map<FrameID, std::unique_ptr<sf::IntRect>>& getFrameCord()
	{
		return m_frameBoxRects;
	}
	sf::RenderWindow& getWindow()
	{
		return m_window;
	}

private:
	sf::RenderWindow m_window;
	std::unordered_map<Colors, std::unique_ptr<sf::Color>> m_colors;
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;

	std::unordered_map<TileID, std::unique_ptr<sf::Sprite>> m_tileSprites;
	std::unordered_map<TileID, sf::IntRect> m_tileIdRects;

	std::unordered_map<FrameID, std::unique_ptr<sf::IntRect>> m_frameBoxRects;
	std::unique_ptr<sf::Font> m_font;
	
	//------
	
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	Resources()
		: m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Grid Movement Game")
	{
		m_window.setFramerateLimit(FPS);

		sf::Vector2i startIndexs(3, 61);
		sf::Vector2i size(TILE_SIZE, TILE_SIZE);

		m_tileIdRects[GRASS] = sf::IntRect(startIndexs, size);

		startIndexs += sf::Vector2i(0, TILE_SIZE+1);

		m_tileIdRects[TALLGRASS] = sf::IntRect(startIndexs, size);

		loadTileSpriteSheet("tileset.png", m_tileIdRects);

		// std::cout << "after loading tileset.png" << std::endl;
	};

	void loadTileSpriteSheet(const std::string& filename, const std::unordered_map<TileID, sf::IntRect>& tileRects)
	{
		sf::Texture& texture = getTexture(filename);

		for (const auto& pair : tileRects)
		{
			TileID tileId = pair.first;
			const sf::IntRect& rect = pair.second;

			std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>(texture, rect);
			m_tileSprites[tileId] = std::move(sprite);
		}
	}
};
