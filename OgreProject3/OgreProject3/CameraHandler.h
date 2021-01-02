#pragma once
#include <Ogre.h>
#include "Character.h"

using namespace Ogre;

class CameraHandler
{
private:
	SceneNode* camNode;
	SceneNode* lightNode;
	Light* spotLight;
	Character* quarry;
	SceneManager* sceneMgr;
	Vector3 lastPoint;
	Vector3 offSet;
	Vector3 offSet2;
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