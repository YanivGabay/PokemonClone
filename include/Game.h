#pragma once
#include <iostream>

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

#include "Camera.h"
#include "entity/Player.h"
#include "world/TilesMap.h"
#include "Tile.h"
#include "Resources.h"
#include "StateMachine.h"
class Game
{
public:
	Game()
	{
		runGame();
	}

	~Game()
	{
	}
	void runGame()
	{
        auto stateMachine = std::make_unique<StateMachine>();
        stateMachine->runGame();
       
        
	}

private:

};
