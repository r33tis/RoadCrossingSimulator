#include "GameController.h"
#include <iostream>

void GameController::init(SceneManager* sceneMgr, Character* quarry, float endTime) {
	this->time = 0.0;
	this->endTime = endTime;
	this->bestDistance = 0.0;
	this->quarry = quarry;
	this->sceneMgr = sceneMgr;
	updateAmbience();
}

void GameController::update(Real elapsedTime, OIS::Keyboard* input) {
	time += elapsedTime;

	//TODO: Replace score with UI and stop printing out time.
	std::cout << "Time: "<< time << "/" << endTime << "\t" << "Score: " << bestDistance << "\n";

	float distance = -quarry->getZ();
	if (distance > bestDistance) {
		bestDistance = distance;
	}

	updateAmbience();
}

void GameController::updateAmbience() {
	float v = (endTime - time) / endTime;
	if (v < 0.0) { v = 0.0; }
	if (v > 1.0) { v = 1.0; }
	
	//TODO: Different bands of light die down at different rates, so we get a cool sunset.
	float r = 1.0 * v;
	float g = 1.0 * v;
	float b = 1.0 * v;

	sceneMgr->setAmbientLight(Ogre::ColourValue(r, g, b));
}