#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

#include "StateMachine.h"
#include "world/TilesMap.h"
#include "SoundTon.h"
#include "utilities.h"


class Game
{
public:
	Game()
	{
		SoundTon::getInstance().playSound(soundNames::OPEN);
		SoundTon::getInstance().stopSound(soundNames::OPEN);
	};

	~Game() = default;
	
	void runGame()
	{
        auto stateMachine = std::make_unique<StateMachine>();
        stateMachine->runGame();
	}

private:

};
