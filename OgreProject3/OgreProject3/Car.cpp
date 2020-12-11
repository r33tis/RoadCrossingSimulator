#include "Car.h"
#include <sstream>

void Car::create(SceneManager* sceneMgr, float x, float y, float z, float speed) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));
    mEntity = mSceneMgr->createEntity(mName, "Cube.mesh");
    mMainNode->attachObject(mEntity);
    this->speed = speed;
    //TODO: Rotation according to direction (speed)
    if (speed > 0.0) {
    }
    else {
    }
    std::cout << "unhandled rotation for new car !!!\n";
}

void Car::update(Real elapsedTime) {
    mMainNode->translate(Vector3(0, 0, speed));
}

Real x() {
    std::cout << "Function not implemented !!!\n";
    return 0.0;
}
