#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


#include <unordered_map>
#include <memory>
#include <iostream>
#include <array>

const int TILE_SIZE = 16;

enum TileID
{
	ROCK,
	FLOWER,
	GRASS,
	TALLGRASS
	
};

class Resources
{
public:
	static Resources& getInstance()
	{
		static Resources instance;
		return instance;
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

	


private:
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
	std::unordered_map<TileID, std::unique_ptr<sf::Sprite>> m_tileSprites;
	std::unordered_map<TileID, sf::IntRect> m_tileRects;
	std::unique_ptr<sf::Font> m_font;
	
	
	Resources()
	{
		sf::Vector2i startIndexs(3, 61);
		sf::Vector2i size(TILE_SIZE, TILE_SIZE);

		m_tileRects[GRASS] = sf::IntRect(startIndexs, size);
		startIndexs = startIndexs + sf::Vector2i(0, TILE_SIZE+1);
		m_tileRects[TALLGRASS] = sf::IntRect(startIndexs, size);

		loadTileSpriteSheet("tileset.png", m_tileRects);
		std::cout << "after loading tileset.png" << std::endl;
	};

	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

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