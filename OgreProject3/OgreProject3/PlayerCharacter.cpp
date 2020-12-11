#include "PlayerCharacter.h"
#include <sstream>
#include "DummyCharacter.h"

void PlayerCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->loadModel("Cube", "studentColors.PNG");
}

void PlayerCharacter::update(Real elapsedTime, OIS::Keyboard* input) {
    if (this->placeMeeting<DummyCharacter>(0, 0)) {
        mMainNode->setScale(Vector3(1.5, 1.5, 1.5));
        cout << "collision!";
    }
    else {
        mMainNode->setScale(Vector3(1, 1, 1));
    }

    if (input->isKeyDown(OIS::KC_W)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, 5 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_S)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, -3 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_A)) {
        mMainNode->yaw(Radian(2 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_D)) {
        mMainNode->yaw(Radian(-2 * elapsedTime));
    }
}

