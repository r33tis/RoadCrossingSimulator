#include "Car.h"
#include <sstream>

void Car::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->loadModel("Car", "carColors.png");
    this->speed = 0;
}

void Car::update(Real elapsedTime, OIS::Keyboard* input) {
    mMainNode->translate(Vector3(speed, 0, 0));
}

void Car::setSpeed(float speed) {
    this->speed = speed;

    if (speed > 0.0) {
        mMainNode->yaw(Radian(Degree(-90)));
    }
    else {
        mMainNode->yaw(Radian(Degree(90)));
    }
}
