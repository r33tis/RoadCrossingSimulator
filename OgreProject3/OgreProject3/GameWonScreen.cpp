#include "GameWonScreen.h"
#include <iostream>

using namespace Ogre;

GameWonScreen::GameWonScreen() : Screen()
{
	std::vector<std::string> screens;
	for (int i = 1; i <= 4; i++) {
		auto name = "game_won_" + std::to_string(i);
		screens.push_back(name);
	}
	screens.push_back("game_won_1");
	this->loadScreens(screens);
}
