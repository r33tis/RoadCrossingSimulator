#include "PlayerCharacter.h"
#include <sstream>

void PlayerCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->loadModel("Cube", "studentColors.PNG");

    this->initFlashlight();
}

void PlayerCharacter::initFlashlight() {
    Light* spotLight = this->mSceneMgr->createLight("SpotLight");
    spotLight->setDiffuseColor(254, 255, 213);
    spotLight->setSpecularColor(254, 255, 213);
    spotLight->setType(Light::LT_SPOTLIGHT)
    
    flashlightNode = this->mSceneMgr->getRootSceneNode()->createChildSceneNode();
    flashlightNode->attachObject(spotLight);
    flashlightNode->setDirection(0, -1, -2);
    flashlightNode->setPosition(Vector3(0,1,-0.1));

    spotLight->setSpotlightRange(Degree(), Degree());
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
    if (input->isKeyDown(OIS::KC_Q)) {
        flashlightNode->yaw(Radian(2 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_E)) {
        flashlightNode->yaw(Radian(-2 * elapsedTime));
    }
}

