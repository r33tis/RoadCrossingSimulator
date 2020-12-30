#include "PlayerCharacter.h"
#include "DummyCharacter.h"
#include <OgreLight.h>
#include <sstream>

void PlayerCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->loadModel("Cube", "studentColors.PNG");
    this->speed = 20.0;
    this->indirectSpeed = 10.0;

    this->initFlashlight();
}

void PlayerCharacter::initFlashlight() {
    Light* spotLight = this->mSceneMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(0.4, 0.3, 0.3);
    spotLight->setSpecularColour(0.4, 0.3, 0.3);
    spotLight->setType(Light::LT_SPOTLIGHT);
    
    SceneNode* flashlight = mMainNode->createChildSceneNode();
    flashlight->attachObject(spotLight);
    flashlight->setDirection(0, -1, 2);
    flashlight->getParentSceneNode()->removeChild(flashlight);
    flashlightNode = mMainNode->createChildSceneNode();
    flashlightNode->addChild(flashlight);
    flashlightNode->setPosition(Vector3(0, 6, -0.1));

    spotLight->setSpotlightRange(Degree(35), Degree(50));
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
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, speed * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_S)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, -speed * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_A)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(speed * elapsedTime, 0, 0));
    }
    if (input->isKeyDown(OIS::KC_D)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(-speed * elapsedTime, 0, 0));
    }
    
    if (input->isKeyDown(OIS::KC_Q)) {
        flashlightNode->yaw(Radian(2 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_E)) {
        flashlightNode->yaw(Radian(-2 * elapsedTime));
    }
}

