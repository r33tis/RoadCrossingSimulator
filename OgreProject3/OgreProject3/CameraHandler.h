#pragma once
#include <Ogre.h>
#include "Character.h"

using namespace Ogre;

class CameraHandler
{
private:
	SceneNode* camNode;
	Character* quarry;
	SceneManager* sceneMgr;
	Vector3 lastPoint;
	float t;
	float speed;
	CameraHandler() {};
public:
	static CameraHandler* getInstance() {
		static CameraHandler instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, Character* quarry, float speed);
	void update(Real elaspedTime, OIS::Keyboard* input);
	Camera* createCamera();
};