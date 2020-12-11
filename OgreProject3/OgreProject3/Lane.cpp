#include "Lane.h"
#include <iostream>

using namespace std;

void Lane::update(Real elapsedTime) {
	timeUntilSpawn -= elapsedTime;
}