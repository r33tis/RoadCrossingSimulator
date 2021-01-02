#pragma once
#include <Ogre.h>
#include <iostream>
#include "Character.h"

using namespace Ogre;

class GameController
{
private:
	float time;
	float endTime;
	float laneLength;
	int bestDistance;
	Character* quarry;
	SceneManager* sceneMgr;
	Light* sky;
	SceneNode* skyNode;
	GameController() {};
public:
	static GameController* getInstance() {
		static GameController instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, Character* quarry, float endTime, float laneLength);
	void update(Real elapsedTIme, OIS::Keyboard* input);
	void updateSky(Real elapsedTime);
	void updateScore(int distance);
};