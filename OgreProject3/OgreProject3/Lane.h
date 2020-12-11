#pragma once
#include <Ogre.h>

using namespace Ogre;

class Lane {
public:
	float z;
	float timeUntilSpawn;
	float spawnTime;
	float speed;
	Lane() {
		timeUntilSpawn = 0.0f;
		speed = 1.0f;
	}
	void update(Real elapsedTime);
};