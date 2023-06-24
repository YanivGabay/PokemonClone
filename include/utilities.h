#pragma once
#include <random>


const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

const int TILE_SIZE = 16;

const unsigned int FPS = 60;


// --------------------------------
int generateRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(eng);
}

enum class WhosAttack
{
	Enemy,
	Player
};

enum class LAYERS
{
	LOWER = 1,
	MEDIUM = 2,
	UPPER = 3
};

enum class PlayerID
{
	UP_IDLE,
	UP_MOVE,
	UP_MOVE_2,
	DOWN_IDLE,
	DOWN_MOVE,
	DOWN_MOVE_2,
	LEFT_IDLE,
	LEFT_MOVE,
	LEFT_MOVE_2,
	RIGHT_IDLE,
	RIGHT_MOVE,
	RIGHT_MOVE_2,

	END
};

enum class LevelID
{
	POKE_CENTER,
	START_TOWN,
	START_FIELD,
	SECOND_TOWN,
	SECOND_FIELD,
	MINI_PHYSICS_LEVEL,


	END
};

enum class FrameID
{
	LEFT_UP_CORNER,
	UP_HORIZ,
	RIGHT_UP_CORNER,
	LEFT_VERTICAL,
	MIDDLE,
	RIGHT_VERTICAL,
	LEFT_DOWN_CORNER,
	DOWN_HORIZ,
	RIGHT_DOWN_CORNER,
		//toadd
	END
};
const int SIDES = 4;

enum Side
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

const float SOUND_VOLUME = 5;
enum soundNames { OPEN, BUSH, CITY, BATTLE };
std::vector<std::string> sound_files = { "resources/pokemonOpening.ogg",
										 "resources/bush_step.ogg",
										 "resources/City.ogg",
										 "resources/Battle.ogg" };
