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
	
	}

	~Party()
	{
	}
	
	void addPokemon(std::unique_ptr<Pokemon> pokemon)
	{
		std::cout << "Entering addPokemon method." << std::endl;

		// Check if the pokemon unique_ptr is null
		if (!pokemon)
		{
			std::cout << "Passed pokemon unique_ptr is null." << std::endl;
			return;
		}

		std::cout << "Before loop in addPokemon." << std::endl;

		for (int pokemonIndex = 0; pokemonIndex < PARTY_SIZE; pokemonIndex++)
		{
			std::cout << "Inside the loop in addPokemon, index: " << pokemonIndex << std::endl;

			// Check if the current slot in m_pokemons is null before checking its value
			if (!m_pokemons[pokemonIndex])
			{
				std::cout << "Found empty slot at index: " << pokemonIndex << std::endl;
				m_pokemons[pokemonIndex] = std::move(pokemon);
				std::cout << "Pokemon added to party." << std::endl;
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
	std::array <std::unique_ptr< Pokemon >, PARTY_SIZE > m_pokemons {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}};
};
