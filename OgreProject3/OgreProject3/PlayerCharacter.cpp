#include "PlayerCharacter.h"


PlayerCharacter::PlayerCharacter(String name, SceneManager* sceneMgr) {
    // Setup basic member references
    mName = name;
    mSceneMgr = sceneMgr;

    // Setup basic node structure to handle 3rd person cameras
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);

    // Give this character a shape :)
    mEntity = mSceneMgr->createEntity(mName, "Cube.mesh");
    mMainNode->attachObject(mEntity);
}

PlayerCharacter::~PlayerCharacter() {
    mMainNode->detachAllObjects();
    delete mEntity;
    mMainNode->removeAndDestroyAllChildren();
    mSceneMgr->destroySceneNode(mName);
}

void PlayerCharacter::update(Real elapsedTime, OIS::Keyboard* input) {
    if (input->isKeyDown(OIS::KC_W)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, 2 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_S)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, -1 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_A)) {
        mMainNode->yaw(Radian(2 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_D)) {
        mMainNode->yaw(Radian(-2 * elapsedTime));
    }
}
