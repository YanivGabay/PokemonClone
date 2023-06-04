#pragma once
#include <iostream>

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

#include <memory>
#include <vector>
#include "StateMachine.h"
#include "world/TilesMap.h"
#include <boost/signals2.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>
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
