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
		std::cout << "before add pokemon in party" << std::endl;
		// Find an empty slot in the party and add the Pokemon

		for (int pokemonIndex = 0; pokemonIndex < PARTY_SIZE; pokemonIndex++)
		{
			if (m_pokemons[pokemonIndex] == nullptr)
				m_pokemons[pokemonIndex] = std::move(pokemon);
		}
		std::cout << "after add pokemon in party" << std::endl;
		/*
		for (auto& slot : m_pokemons)
		{
			if (!slot)
			{
				std::cout << "Slot is empty, adding pokemon: " << std::endl;
				slot = std::move(pokemon);
				std::cout << "Pokemon added, slot: " << std::endl;
				break;
			}
		}
		std::cout << "after add pokemon in party" << std::endl;
		*/
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
