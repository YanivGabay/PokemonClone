#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <array>
#include <string>
#include "Utilities/PokemonIndex.h"
#include "tileson/tileson.hpp"
#include "utilities.h"


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
				throw std::runtime_error("Failed to load texture.");
			}
		}
		
		return *m_textures[filename];
	}
	
	sf::Font& getFont()
	{
		if (!m_font)
		{
			throw std::runtime_error("Font has not been loaded.");
		}

		return *m_font;
	}
	
	void loadPlayerRects()
	{
		sf::Vector2i size = sf::Vector2i(22, 26);
		sf::Vector2i position = sf::Vector2i(0, 0);
		
		for (PlayerID id = PlayerID::UP_IDLE; id != PlayerID::END; id = static_cast<PlayerID>(static_cast<int>(id) + 1))
		{
			int row = static_cast<int>(id) / 3;  // Calculate the row index
			int col = static_cast<int>(id) % 3;  // Calculate the column index

			position.x = col * (22);   // Update the x position
			position.y = row * (26);   // Update the y position

			m_playerRects[id] = std::make_unique<sf::IntRect>(position.x, position.y, size.x, size.y);
		}
	}
	
	void loadFrames()
	{
		sf::Vector2i size = sf::Vector2i(TILE_SIZE/2, TILE_SIZE / 2);
		sf::Vector2i position = sf::Vector2i(0, 0);
		
		loadFont("resources/fonts/Pokemon.ttf");
		
		for (FrameID id = FrameID::LEFT_UP_CORNER; id != FrameID::END; id = static_cast<FrameID>(static_cast<int>(id) + 1))
		{
			int row = static_cast<int>(id) / 3;  // Calculate the row index
			int col = static_cast<int>(id) % 3;  // Calculate the column index
			
			position.x = col * (TILE_SIZE / 2);   // Update the x position
			position.y = row * (TILE_SIZE / 2);   // Update the y position
			
			m_frameBoxRects[id] = std::make_unique<sf::IntRect>(position.x,position.y, size.x,size.y);
		}
	}
	
	void loadFont(const std::string& filename)
	{
		if (m_font)
		{
			throw std::runtime_error("Font has already been loaded.");
		}
		
		m_font = std::make_unique<sf::Font>();
		
		if (!m_font->loadFromFile(filename))
		{
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
	
	sf::IntRect& getRect(PlayerID id)
	{
		if (m_playerRects.find(id) == m_playerRects.end())
		{
			throw std::runtime_error("Failed to load texture.");
		}
		
		return *m_playerRects[id];
	}
	
	sf::IntRect& getRect(NpcId id)
	{
		if (m_npcRects.find(id) == m_npcRects.end())
		{
			throw std::runtime_error("Failed to load texture.");
		}

		return *m_npcRects[id];
	}
	
	std::pair<sf::Sprite, sf::Sprite> getPokemonSprites(enum PokemonIndex name)
	{
		if (m_pokemonSprite.find(name) == m_pokemonSprite.end())
		{
			throw std::runtime_error("Failed to load texture.");
		}

		return m_pokemonSprite[name];
	}
	
	void loadPokemonSprites()
	{
		const std::string frontFolderPath = "resources/pokemonSpritesSheet/";
		const std::string backFolderPath = "resources/pokemonSpritesSheet/back/";

		for (int i = 0; i < pokemonFiles.size(); ++i)
		{
			enum PokemonIndex name;
			const std::string spriteLabel = pokemonFiles[i];

			name = static_cast<PokemonIndex>(stoi(spriteLabel));
			// Load the front sprite
			
			std::string frontSpriteFilename = frontFolderPath + spriteLabel + ".png";
			sf::Texture& frontTexture = getTexture(frontSpriteFilename);
			sf::Sprite frontSprite(frontTexture);
			// Set positions, scales, or other properties as needed

			// Load the back sprite
			
			std::string backSpriteFilename = backFolderPath + spriteLabel + ".png";
			sf::Texture& backTexture = getTexture(backSpriteFilename);
			sf::Sprite backSprite(backTexture);
			// Set positions, scales, or other properties as needed

			m_pokemonSprite[name] = std::make_pair(frontSprite, backSprite);
		}
	}
	
	void loadNpcSprites()
	{
		sf::Vector2i size = sf::Vector2i(16, 21);
		sf::Vector2i position = sf::Vector2i(0, 0);
		
		for (NpcId id = NpcId::HealDown; id != NpcId::END; id = static_cast<NpcId>(static_cast<int>(id) + 1))
		{
			int row = static_cast<int>(id) / 4;  // Calculate the row index
			int col = static_cast<int>(id) % 4;  // Calculate the column index

			position.x = col * (16);   // Update the x position
			position.y = row * (21);   // Update the y position

			m_npcRects[id] = std::make_unique<sf::IntRect>(position.x, position.y, size.x, size.y);
		}
	}
	
private:
	sf::RenderWindow m_window;
	
	std::unordered_map<Colors, std::unique_ptr<sf::Color>> m_colors;
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
	std::unordered_map<FrameID, std::unique_ptr<sf::IntRect>> m_frameBoxRects;
	std::unordered_map<PlayerID, std::unique_ptr<sf::IntRect>> m_playerRects;
	std::unordered_map<NpcId, std::unique_ptr<sf::IntRect>> m_npcRects;

	std::unique_ptr<sf::Font> m_font;

	std::unordered_map<enum PokemonIndex, std::pair<sf::Sprite, sf::Sprite>> m_pokemonSprite;


	//------
	
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	Resources()
		: m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Grid Movement Game")
		
	{
		m_window.setFramerateLimit(FPS);
		
		sf::Vector2i startIndexs(3, 61);
		sf::Vector2i size(TILE_SIZE, TILE_SIZE);
		getTexture("resources/spritesheet.png");
		getTexture("resources/battlegroundSprites.png");
		getTexture("resources/background.png");
		loadFrames();
		loadPlayerRects();
		loadPokemonSprites();
	}
};
