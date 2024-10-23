#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include "StateMachine.h"
#include "world/TilesMap.h"
#include "SoundTon.h"
#include "utilities.h"

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)

#pragma warning(pop)


class Game
{
public:
	Game()
	{
		SoundTon::getInstance().playSound(soundNames::OPEN);
	}

	~Game() = default;
	
	void runGame()
	{
        auto stateMachine = std::make_unique<StateMachine>();
        stateMachine->runGame();
	}

private:

};
