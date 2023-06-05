#pragma once


const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

const int TILE_SIZE = 16;

const unsigned int FPS = 60;

// --------------------------------

//if you add another, add it to Resourcses::TUPLE

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
	enum class MapID
	{
		ROCK,
		FLOWER,
		GRASS,
		TALLGRASS,
		//toadd

		END

	};

enum Side
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
