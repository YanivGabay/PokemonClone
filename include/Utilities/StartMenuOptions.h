#pragma once

#include <optional>


const int MENU_OPTIONS = 3;

enum StartMenuOptions
{
	NEW_GAME,
	LOAD_GAME,
	QUIT
};

std::optional<StartMenuOptions> operator++(std::optional<StartMenuOptions> option)
{
	if (option)
	{
		*option = static_cast<StartMenuOptions>((static_cast<int>(*option) + 1) % MENU_OPTIONS);
	}
	
	return option;
}

std::optional<StartMenuOptions> operator--(std::optional<StartMenuOptions> option)
{
	if (option)
	{
		int value = static_cast<int>(*option) - 1;
		if (value < 0)
			value = MENU_OPTIONS - 1;
		*option = static_cast<StartMenuOptions>(value);
	}
	return option;
}
