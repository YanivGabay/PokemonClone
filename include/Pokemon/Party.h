#pragma once
#include "Pokemon.h"
#include <array>
const int PARTY_SIZE = 6;
class Party
{
public:
	Party()
	{
		for (auto& slot : m_pokemons)
		{
			slot = nullptr;
		}
	}

	~Party()
	{
	}
	
	void addPokemon(std::unique_ptr<Pokemon> pokemon)
	{
		// Find an empty slot in the party and add the Pokemon
		for (auto& slot : m_pokemons)
		{
			if (!slot)
			{
				slot = std::move(pokemon);
				break;
			}
		}
	}
private:
	std::array <std::unique_ptr< Pokemon > , PARTY_SIZE > m_pokemons;
};
