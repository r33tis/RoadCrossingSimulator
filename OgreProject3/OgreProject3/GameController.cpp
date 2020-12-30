#include "GameController.h"
#include <iostream>
#include <tgmath.h>

void GameController::init(SceneManager* sceneMgr, Character* quarry, float endTime) {
	this->time = 0.0;
	this->endTime = endTime;
	this->bestDistance = 0.0;
	this->quarry = quarry;
	this->sceneMgr = sceneMgr;
	this->sky = this->sceneMgr->createLight("DirectionalLight");
	this->sky->setType(Light::LT_DIRECTIONAL);
	this->sky->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	this->sky->setSpecularColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	this->skyNode = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	this->skyNode->attachObject(this->sky);
	this->skyNode->setDirection(Vector3(0, -1, 0));
	updateSky(0);
}

void GameController::update(Real elapsedTime, OIS::Keyboard* input) {
	time += elapsedTime;

	//TODO: Replace score with UI and stop printing out time.
	//std::cout << "Time: "<< time << "/" << endTime << "\t" << "Score: " << bestDistance << "\n";

	float distance = -quarry->getZ();
	if (distance > bestDistance) {
		bestDistance = distance;
	}

	updateSky(elapsedTime);
}

void GameController::updateSky(Real elapsedTime) {
	float v = (endTime - time) / endTime;
	if (v < 0.0) { v = 0.0; }
	else if (v > 1.0) { v = 1.0; }
	else {
		this->skyNode->pitch(Radian(Degree(elapsedTime)));
		this->skyNode->roll(Radian(Degree(elapsedTime)));
	}

	//TODO: Different bands of light die down at different rates, so we get a cool sunset.
	float r = 1.0 * pow(sin(v * 1.57),0.4); // Slowest going
	float g = 1.0 * pow(sin(v * 1.0), 1); // Fastest going
	float b = 0.9 * (pow(v - 0.1, 5) + pow(v - 0.8, 8));

	this->sky->setDiffuseColour(Ogre::ColourValue(r, g, b));
	this->sky->setSpecularColour(Ogre::ColourValue(r, g, b));
}