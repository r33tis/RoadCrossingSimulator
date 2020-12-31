#include "Car.h"
#include <sstream>

void Car::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    //std::vector<const char*> v_car { "Car", "carColors.png" };
    //std::vector<const char*> v_jeep { "jeep", "jeepColors.png" };

    //choices.push
    std::vector< std::vector<const char*> > choices;
    choices.push_back(std::vector<const char*> { "Car", "carColors.png" });
    choices.push_back(std::vector<const char*> { "jeep", "jeepColors.png" });
    choices.push_back(std::vector<const char*> { "lorry", "lorryColors.png" });

    std::vector<std::vector<const char*>>::iterator randIt = choices.begin();
    std::advance(randIt, std::rand() % choices.size());

    this->loadModel(randIt->at(0), randIt->at(1));
    //this->loadModel("Car", "carColors.png");
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
