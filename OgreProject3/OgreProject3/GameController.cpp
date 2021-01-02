#include "GameController.h"
#include <iostream>
#include <tgmath.h>
#include <stack>

void GameController::init(SceneManager* sceneMgr, Character* quarry, float endTime, float laneLength) {
	this->time = 0.0;
	this->endTime = endTime;
	this->laneLength = laneLength;
	this->bestDistance = 0;
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

	int distance = (-quarry->getZ() / laneLength);
	if (distance > bestDistance) {
		bestDistance = distance;
		updateScore(distance);
	}

	updateSky(elapsedTime);
}

void GameController::updateSky(Real elapsedTime) {
	float v = (endTime - time) / endTime;
	if (v < 0.0) { v = 0.0; }
	else if (v > 1.0) { v = 1.0; }
	else {
		float shift = elapsedTime * 100 / endTime;
		this->skyNode->pitch(Radian(Degree(shift)));
		this->skyNode->roll(Radian(Degree(shift)));
		this->skyNode->yaw(Radian(Degree(shift)));
	}

	//TODO: Different bands of light die down at different rates, so we get a cool sunset.
	float r = 1.0 * pow(sin(v * 1.57),0.4); // Slowest going
	float g = 1.0 * pow(sin(v * 1.0), 1); // Fastest going
	float b = 0.9 * (pow(v - 0.1, 5) + pow(v - 0.8, 8));

	this->sky->setDiffuseColour(Ogre::ColourValue(r, g, b));
	this->sky->setSpecularColour(Ogre::ColourValue(r, g, b));
}

void GameController::updateScore(int distance) {
	int total = distance;
	std::cout << "D:" << distance << "\n";

	int order = 1;
	while (order <= total) {
		order *= 10;
	}

	std::stack <int> numbers;
	int orderFloor = order / 10;
	while (orderFloor >= 1) {
		int counter = 0;
		while (total >= orderFloor) {
			total -= orderFloor;
			counter++;
		}
		numbers.push(counter);
		orderFloor /= 10;
	}

	while (!numbers.empty()) {
		std::cout << numbers.top();
		numbers.pop();
	}
	std::cout << "\n";
}