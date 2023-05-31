#pragma once


const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

const int TILE_SIZE = 16;

const unsigned int FPS = 60;

// --------------------------------

enum TileID
{
	ROCK,
	FLOWER,
	GRASS,
	TALLGRASS
};

enum Side
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
