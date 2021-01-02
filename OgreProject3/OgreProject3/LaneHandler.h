#pragma once
#include <vector>
#include <random>
#include <Ogre.h>
#include <string>
#include "Lane.h"
#include "Car.h"
#include "SpaceClamper.h"

class LaneHandler
{
private:
	float leftBound;
	float rightBound;
	float laneLength;
	std::vector<Lane*> lanes;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> speedDis;
	std::uniform_real_distribution<> spawnDis;
	std::uniform_int_distribution<> pauseDis;
	std::uniform_int_distribution<> twoDis;
	SceneManager* sceneMgr;
	LaneHandler() {};
public:
	static LaneHandler* getInstance() {
		static LaneHandler instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, float laneLength, float leftBound, float rightBound, float speedMin, float speedMax, float spawnMin, float spawnMax, float pauseMin, float pauseMax);
	void update(Real elaspedTime, OIS::Keyboard* keyboard, OIS::Mouse* mouse);
public:
	void createLanes(int n);
	Lane* createLane(float z);
	void createPause(float z);
	void createDragLight(float x1, float x2, float z);
	Car* createCar(Lane* lane);
	std::vector<Lane*> listLanes();
};

inline Car* LaneHandler::createCar(Lane* lane) {
	float speed = lane->speed;
	float x = leftBound + speed;
	if (speed < 0.0) { x = rightBound + speed; }
	float z = lane->z;

	CharacterHandler* charHandler = CharacterHandler::getInstance();
	Car* car = (Car*) charHandler->createCharacter<Car>(x, 0, z);
	car->setSpeed(speed);

	return car;
}

inline Lane* LaneHandler::createLane(float z)
{
	Lane* lane = new Lane();

	lane->z = z;

	float sign = 1.0;
	if (twoDis(gen) == 0) { sign = -1.0; }
	lane->speed = (speedDis(gen)) * sign;
	lane->spawnTime = spawnDis(gen) * 0.5;
	lane->timeUntilSpawn = lane->spawnTime;

	return lane;
}

inline void LaneHandler::createDragLight(float x1, float x2, float z) {
	float locX = SpaceClamper::getInstance()->clampX(x1);
	float locY = SpaceClamper::getInstance()->clampY(1.0);
	float locZ = SpaceClamper::getInstance()->clampZ(z);

	Light* spotLight = this->sceneMgr->createLight("SpotLight" + std::to_string(locX) + std::to_string(locZ));
	spotLight->setDiffuseColour(0.9, 0.85, 0.95);
	spotLight->setSpecularColour(0.9, 0.85, 0.95);
	spotLight->setType(Light::LT_SPOTLIGHT);
	spotLight->setCastShadows(false);

	SceneNode* flashlight = sceneMgr->createSceneNode();
	flashlight->attachObject(spotLight);
	flashlight->setDirection(x2 - x1, -1, 0);
	flashlight->setPosition(Vector3(locX, locY, locZ));

	spotLight->setSpotlightRange(Degree(5), Degree(10), 0.05);
}

inline void LaneHandler::createPause(float z) {
	//TOO COSTLY!
	//createDragLight(leftBound - 2*laneLength, rightBound + 2*laneLength, z);
	//createDragLight(rightBound + 2*laneLength, leftBound - 2*laneLength, z);


}

inline void LaneHandler::createLanes(int n)
{
	int lanesUntilPause = 0;
	for (int i = 0; i < n; i++) {
		if (lanesUntilPause <= 0) {
			// Would a pause lane still be a lane, just of a different kind?
			createPause(SpaceClamper::getInstance()->clampZ(-float(i) * laneLength));
			lanesUntilPause = pauseDis(gen);
		}
		else {
			Lane* lane = createLane(SpaceClamper::getInstance()->clampZ(-float(i) * laneLength));
			lanes.push_back(lane);
			lanesUntilPause--;
		}
	}
}