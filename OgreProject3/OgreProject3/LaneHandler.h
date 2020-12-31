#pragma once
#include <vector>
#include <random>
#include <Ogre.h>
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
	std::uniform_real_distribution<> pauseDis;
	std::uniform_real_distribution<> coinDis;
	SceneManager* sceneMgr;
	LaneHandler() {};
public:
	static LaneHandler* getInstance() {
		static LaneHandler instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, float laneLength, float leftBound, float rightBound, float speedMin, float speedMax, float spawnMin, float spawnMax, float pauseMin, float pauseMax);
	void update(Real elaspedTime, OIS::Keyboard* input);
public:
	void createLanes(int n);
	Lane* createLane(float z);
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
	if (coinDis(gen) <= 0.0) { sign = -1.0; }
	lane->speed = (speedDis(gen)) * sign;
	lane->spawnTime = spawnDis(gen) * 0.5;
	lane->timeUntilSpawn = lane->spawnTime;

	return lane;
}

inline void LaneHandler::createLanes(int n)
{
	int lanesUntilPause = 0;
	for (int i = 0; i < n; i++) {
		if (lanesUntilPause <= 0) {
			// Would a pause lane still be a lane, just of a different kind?
			lanesUntilPause = pauseDis(gen);
		}
		else {
			Lane* lane = createLane(SpaceClamper::getInstance()->clampZ(-float(i) * laneLength));
			lanes.push_back(lane);
			lanesUntilPause--;
		}
	}
}