#pragma once
#include <vector>
#include <random>
#include <Ogre.h>
#include "Lane.h"
#include "Car.h"

class LaneHandler
{
private:
	float leftBound;
	float rightBound;
	std::vector<Lane*> lanes;
	std::vector<Car*> cars;
	std::queue<Car*> deleteQueue;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> speedDis;
	std::uniform_real_distribution<> spawnDis;
	std::uniform_real_distribution<> coinDis;
	SceneManager* sceneMgr;
	LaneHandler() {};
public:
	static LaneHandler* getInstance() {
		static LaneHandler instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, float leftBound, float rightBound, float speedMin, float speedMax, float spawnMin, float spawnMax);
	void update(Real elaspedTime);
public:
	void createLanes(int n);
	Lane* createLane(float z);
	Car* createCar(Lane* lane);
	void deleteCar(Car* car);
	std::vector<Lane*> listLanes();
	std::vector<Car*> listCars();
};

inline Car* LaneHandler::createCar(Lane* lane) {
	float speed = lane->speed;
	float x = leftBound + speed;
	if (speed < 0.0) { x = rightBound + speed; }
	float z = lane->z;

	Car* car = new Car();
	car->create(sceneMgr, x, 0, z, speed);
	cars.push_back(car);

	return car;
}

inline void LaneHandler::deleteCar(Car* car) {
	deleteQueue.push(car);
}

inline Lane* LaneHandler::createLane(float z)
{
	Lane* lane = new Lane();

	lane->z = z;

	float sign = 1.0;
	if (coinDis(gen) <= 0.0) { sign = -1.0; }
	lane->speed = (speedDis(gen)) * sign;
	lane->spawnTime = spawnDis(gen);
	lane->timeUntilSpawn = lane->spawnTime;

	return lane;
}

inline void LaneHandler::createLanes(int n)
{
	float laneLength = 1.0;
	for (int i = 0; i < n; i++) {
		Lane* lane = createLane(float(i) * laneLength);
		lanes.push_back(lane);
	}
}