#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <memory>
#include <iostream>
#include <array>

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
	std::unique_ptr<sf::Font> m_font;

	Resources()
			{
	}

	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	
};