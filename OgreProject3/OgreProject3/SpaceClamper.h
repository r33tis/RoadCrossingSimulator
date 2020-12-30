#include <Ogre.h>

#pragma once
class SpaceClamper
{
public:
	enum class clampMode
	{
		floor, ceil, centre
	};
	static SpaceClamper* getInstance() {
		static SpaceClamper instance;
		return &instance;
	}
	void init(float xSpace, float ySpace, float zSpace, clampMode mode);
private:
	clampMode mode;
	float xSpace;
	float ySpace;
	float zSpace;
	SpaceClamper() {};

public:
	float clamp(float val, float space);
	float clampX(float x);
	float clampY(float y);
	float clampZ(float z);
	Ogre::Vector3 clamp(float x, float y, float z);
	Ogre::Vector3 clamp(Ogre::Vector3 vector);
};


