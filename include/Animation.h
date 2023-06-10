#pragma once
#include "Resources.h"

template <class T >
class Animation
{
public:
	Animation()
	{
	}

	~Animation()
	{
	}

private:
	std::unordered_map<T, std::pair<std::vector<sf::IntRect>, float>> sequences;
	sf::Sprite m_sprite;
	std::reference_wrapper<sf::Texture> m_texture;

};
