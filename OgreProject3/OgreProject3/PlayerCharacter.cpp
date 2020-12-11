#include "PlayerCharacter.h"
#include <sstream>
#include "DummyCharacter.h"


void PlayerCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->loadModel("Cube", "studentColors.PNG");

    targetPosition = Vector3(x, y, z);
    velocity = Vector3(0, 0, 0);
}

void PlayerCharacter::update(Real elapsedTime, OIS::Keyboard* input) {
    if (this->placeMeeting<DummyCharacter>(0, 0)) {
        mMainNode->setScale(Vector3(1.5, 1.5, 1.5));
        //cout << "collision!";
    }
    else {
        mMainNode->setScale(Vector3(1, 1, 1));
    }

    if (input->isKeyDown(OIS::KC_W)) {
        targetPosition.z = round(getZ() / 5.0) * 5.0 + 5;
    }
    if (input->isKeyDown(OIS::KC_S)) {
        targetPosition.z = round(getZ() / 5.0) * 5.0 - 5;
    }
    if (input->isKeyDown(OIS::KC_A)) {
        targetPosition.x = round(getX() / 5.0) * 5.0 - 5;
    }
    if (input->isKeyDown(OIS::KC_D)) {
        targetPosition.x = round(getX() / 5.0) * 5.0 + 5;
    }
    auto position = mMainNode->getPosition();
    auto step = (targetPosition - position);
    Vector3 dir;
    if (step.length() > 1.0) {
        dir = step.normalisedCopy();
    }
    else {
        dir = step;
    }
    float maxSpeed = 2.0;

    velocity += (dir * 0.3);
    velocity -= velocity.normalisedCopy() * min(step.length(), Ogre::Real(0.1));
    velocity = velocity.normalisedCopy() * min(min(velocity.length(), step.length()), maxSpeed);


    mMainNode->translate(velocity);
}

