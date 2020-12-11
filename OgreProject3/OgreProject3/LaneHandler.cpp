#include "LaneHandler.h"

void LaneHandler::init(SceneManager* sceneMgr, float leftBound, float rightBound, float speedMin, float speedMax, float spawnMin, float spawnMax)
{
	this->leftBound = leftBound;
	this->rightBound = rightBound;
	this->lanes = std::vector<Lane*>();
	this->gen = std::mt19937(rd());
	this->speedDis = std::uniform_real_distribution<> (speedMin, speedMax);
	this->spawnDis = std::uniform_real_distribution<> (spawnMin, spawnMax);
	this->coinDis = std::uniform_real_distribution<>(-1.0, 1.0);
	this->sceneMgr = sceneMgr;
}

void LaneHandler::update(Real elapsedTime, OIS::Keyboard* input)
{
	CharacterHandler* characterHandler = CharacterHandler::getInstance();

	for (Lane* lane : lanes) {
		lane->update(elapsedTime);
		if (lane->timeUntilSpawn <= 0.0) {
			lane->timeUntilSpawn = lane->spawnTime;

			createCar(lane);
		}
	}

	std::vector<Character*> cars = characterHandler->listClassCharacters<Car>();

	for (Character* car : cars) {
		car->update(elapsedTime, input);
		float x = car->getX();

		if (x < leftBound || x > rightBound) {
			characterHandler->deleteCharacter(car);
		}
	}
}