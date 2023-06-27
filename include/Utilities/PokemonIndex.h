#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include "utilities.h"


std::vector<std::string> pokemonFiles { "1", "3", "4", "6",
"7", "9", "17", "25",
"56", "69", "88", "144", "145", "146", "382", "383", "384" };

enum class PokemonIndex
{
	BULBASOR = 1,
	VENASUR = 3,
	CHARMANDER = 4,
	CHARIZARD = 6,
	SQUIRTLE = 7,
	BLASTOISE = 9,
	PIGEOT = 17,
	PIKACHU = 25,
	MONKEY = 56,
	LEAF = 69,
	MUD = 88,
	ICEBIRD = 144,
	ELECTROBIRD = 145,
	FIREBIRD = 146,
	BIGWHALOS = 382,
	REDMONSTER = 383,
	GREENIGHTMARE = 384,
	////.......

	END
};

std::vector <PokemonIndex> FirstLevel
{
	PokemonIndex::VENASUR,
		PokemonIndex::PIGEOT,
		PokemonIndex::LEAF
};
std::vector <PokemonIndex> SecondLevel
{
	PokemonIndex::MONKEY,
		PokemonIndex::MUD,
		PokemonIndex::LEAF,
		PokemonIndex::PIKACHU
};

std::vector <PokemonIndex> ThirdLevel
{
	PokemonIndex::ICEBIRD,
		PokemonIndex::ELECTROBIRD,
		PokemonIndex::FIREBIRD,
		PokemonIndex::BIGWHALOS,
		PokemonIndex::REDMONSTER
};
std::vector <PokemonIndex> FourthLevel
{
			PokemonIndex::GREENIGHTMARE
};
PokemonIndex getRandom(std::vector<PokemonIndex> options)
{
	return options[generateRandomNumber(0, options.size() - 1)];
}

const std::unordered_map<enum PokemonIndex, std::string> PokemonNames =
{

	{ PokemonIndex::BULBASOR, "BULBASOR" },
	{ PokemonIndex::VENASUR, "VENASUR" },
	{ PokemonIndex::CHARMANDER, "CHARMANDER" },
	{ PokemonIndex::CHARIZARD, "CHARIZARD" },
	{ PokemonIndex::SQUIRTLE, "SQUIRTLE" },
	{ PokemonIndex::BLASTOISE, "BLASTOISE" },
	{ PokemonIndex::PIGEOT, "PIGEOT" },
	{ PokemonIndex::PIKACHU, "PIKACHU" },
	{ PokemonIndex::MONKEY, "MONKEY" },
	{ PokemonIndex::LEAF, "LEAF" },
	{ PokemonIndex::MUD, "MUD" },
	{ PokemonIndex::ICEBIRD, "ICEBIRD" },
	{ PokemonIndex::ELECTROBIRD, "ELECTROBIRD" },
	{ PokemonIndex::FIREBIRD, "FIREBIRD" },
	{ PokemonIndex::BIGWHALOS, "BIGWHALOS" },
	{ PokemonIndex::REDMONSTER, "REDMONSTER" },
	{ PokemonIndex::GREENIGHTMARE, "GREENIGHTMARE" }
};


