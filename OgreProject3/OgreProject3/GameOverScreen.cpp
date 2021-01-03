#include "GameOverScreen.h"
#include <iostream>

using namespace Ogre;

GameOverScreen::GameOverScreen() : Screen()
{
	std::vector<std::string> screens;
	for (int i = 1; i <= 3; i++) {
		auto name = "game_over_" + std::to_string(i);
		screens.push_back(name);
	}
	this->loadScreens(screens);
}
