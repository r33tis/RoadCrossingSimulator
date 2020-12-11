#include "DummyCharacter.h"
#include <sstream>

void DummyCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->loadModel("Car", "carColors.png");
}

void DummyCharacter::update(Real elapsedTime, OIS::Keyboard* input) {
}
