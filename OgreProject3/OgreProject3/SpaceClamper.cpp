#include "SpaceClamper.h"
#include <tgmath.h>

void SpaceClamper::init(float xSpace, float ySpace, float zSpace, clampMode mode) {
	this->xSpace = xSpace;
	this->ySpace = ySpace;
	this->zSpace = zSpace;
	this->mode = mode;
}

float SpaceClamper::clamp(float val, float space) {
	
	float value;
	switch (mode) {
	case clampMode::floor:
		value = floorf(val);
		break;
	case clampMode::ceil:
		value = ceilf(val);
		break;
	case clampMode::centre:
		value = (floor(val) + ceil(val)) / 2.0;
		break;
	default:
		value = val;
		break;
	}
		
	return value;
}

float SpaceClamper::clampX(float x) {
	return clamp(x, xSpace);
}

float SpaceClamper::clampY(float y) {
	return clamp(y, ySpace);
}

float SpaceClamper::clampZ(float z) {
	return clamp(z, zSpace);
}

Ogre::Vector3 SpaceClamper::clamp(float x, float y, float z) {
	return Ogre::Vector3(x, y, z);
}

Ogre::Vector3 SpaceClamper::clamp(Ogre::Vector3 vector) {
	return clamp(vector[0], vector[1], vector[2]);
}
