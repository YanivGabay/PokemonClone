#include "Game.h"


int main()
{
	auto game = std::make_unique<Game>();
	game->runGame();

	return EXIT_SUCCESS;
}
