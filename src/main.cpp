#include "Game.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    auto game = std::make_unique<Game>();
    game->runGame();

    return EXIT_SUCCESS;
}
