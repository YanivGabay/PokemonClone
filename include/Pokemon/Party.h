#pragma once
#include "Pokemon.h"
#include <array>
#include "Utilities/PokemonIndex.h"
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
	Pokemon& getPokemon(int index)
	{
		if (index>PARTY_SIZE)
		{
			throw std::runtime_error("party of pokemonms limited to PARTYSIZE");
			exit(0);
		}

		return *m_pokemons[index];
	}
private:
	std::array <std::unique_ptr< Pokemon > , PARTY_SIZE > m_pokemons;
};
