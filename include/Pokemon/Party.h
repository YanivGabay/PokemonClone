#pragma once

#include "Pokemon.h"
#include <array>
#include <iterator>
#include "Utilities/PokemonIndex.h"

const int PARTY_SIZE = 6;

class Party
{
public:
	Party() = default;
	
	~Party() = default;
	
	int getPartySize()
	{
		return PARTY_SIZE;
	}

	void addPokemon(std::unique_ptr<Pokemon> pokemon)
	{
		// Check if the pokemon unique_ptr is null
		if (!pokemon)
		{
			std::cout << "Passed pokemon unique_ptr is null." << std::endl;
			
			return;
		}
		
		for (int pokemonIndex = 0; pokemonIndex < PARTY_SIZE; pokemonIndex++)
		{
			// Check if the current slot in m_pokemons is null before checking its value
			if (!m_pokemons[pokemonIndex])
			{
				m_pokemons[pokemonIndex] = std::move(pokemon);
				
				return;
			}
		}

		std::cout << "Party is full. Cannot add more Pokemon." << std::endl;
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
	std::array <std::unique_ptr< Pokemon >, PARTY_SIZE> m_pokemons { { nullptr,
																	   nullptr,
																	   nullptr,
																	   nullptr,
																	   nullptr,
																	   nullptr } };

};
