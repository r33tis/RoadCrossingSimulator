#include "LaneHandler.h"

void LaneHandler::init(SceneManager* sceneMgr, float leftBound, float rightBound, float speedMin, float speedMax, float spawnMin, float spawnMax)
{
	this->leftBound = leftBound;
	this->rightBound = rightBound;
	this->lanes = std::vector<Lane*>();
	this->cars = std::vector<Car*>();
	this->gen = std::mt19937(rd());
	this->speedDis = std::uniform_real_distribution<> (speedMin, speedMax);
	this->spawnDis = std::uniform_real_distribution<> (spawnMin, spawnMax);
	this->coinDis = std::uniform_real_distribution<>(-1.0, 1.0);
	this->sceneMgr = sceneMgr;
}

void LaneHandler::update(Real elapsedTime)
{
	for (Lane* lane : lanes) {
		lane->update(elapsedTime);
		if (lane->timeUntilSpawn <= 0.0) {
			lane->timeUntilSpawn = lane->spawnTime;
			createCar(lane);
		}
	}

	for (Car* car : cars) {
		car->update(elapsedTime);
		float x = car->x();
		if (x < leftBound || x > rightBound) {
			deleteCar(car);
		}
	}

	while (!deleteQueue.empty()) {
		Car* c = deleteQueue.front();
		if (std::find(cars.begin(), cars.end(), c) != cars.end()) {
			cars.erase(std::remove(cars.begin(), cars.end(), c), cars.end());
			delete c;
		}
		deleteQueue.pop();
	}
}