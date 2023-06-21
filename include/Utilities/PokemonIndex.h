#pragma once
#include <vector>
#include <string>
#include "utilities.h"
std::vector<std::string> pokemonFiles {"1", "4", "6", "7", "17", "25", "56", "69", "88"};
enum class PokemonIndex
{

	BULBASOR = 1,
	CHARMANDER = 4,
	CHARIZARD = 6,
	SQUIRTLE = 7,
	PIGEOT = 17,
	PIKACHU = 25,
	MONKEY = 56,
	LEAF = 69,
	MUD = 88,
	////.......

	END

};
std::vector <PokemonIndex> FirstLevel{PokemonIndex::BULBASOR, PokemonIndex::PIGEOT, PokemonIndex::LEAF};

PokemonIndex getRandom(std::vector<PokemonIndex> options)
{
	return options[generateRandomNumber(0, options.size())];
}
