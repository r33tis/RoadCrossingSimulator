#pragma once
#include <Ogre.h>
class CameraHandler
{
private:
	Character* quarry;
	SceneManager* sceneMgr;
public:
	void init(SceneManager* sceneMgr, Character* quarry);
	void update(Real elaspedTime, OIS::Keyboard* input);
};