#include "Game.h"

#include <iostream>
#include <fstream>
#include "../../external/nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{
    auto game = std::make_unique<Game>();
    game->runGame();

    return EXIT_SUCCESS;
}
