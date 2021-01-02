#pragma once
#include <Ogre.h>
#include <iostream>
#include <stack>
#include <string>
#include <random>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include "Character.h"

using namespace Ogre;

class GameController
{
private:
	float time;
	float endTime;
	float ticker;
	float laneLength;
	int bestDistance;
	Ogre::MaterialPtr numberMaterials[3][10];
	std::stack <int> numbers;
	Character* quarry;
	SceneManager* sceneMgr;
	Light* sky;
	SceneNode* skyNode;
	Overlay* canvas;
	GameController() {};
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> threeDis;
public:
	static GameController* getInstance() {
		static GameController instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, Character* quarry, float endTime, float laneLength);
	void initNumbers();
	void update(Real elapsedTIme, OIS::Keyboard* input);
	void updateSky(Real elapsedTime);
	void updateScore(int distance);
};