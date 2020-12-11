#pragma once
#include <Ogre.h>
#include <iostream>
#include "Character.h"

using namespace Ogre;
using namespace std;

class GameController
{
private:
	float time;
	float endTime;
	float bestDistance;
	Character* quarry;
	SceneManager* sceneMgr;
	GameController() {};
public:
	static GameController* getInstance() {
		static GameController instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, Character* quarry, float endTime);
	void update(Real elapsedTIme, OIS::Keyboard* input);
	void updateAmbience();
};