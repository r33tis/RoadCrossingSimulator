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

    targetPosition = Vector3(x, y, z);
    lastPosition = Vector3(x, y, z);
    movementFulfilled = 0.0;
}

void PlayerCharacter::initFlashlight() {
    Light* spotLight = this->mSceneMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(0.4, 0.3, 0.3);
    spotLight->setSpecularColour(0.4, 0.3, 0.3);
    spotLight->setType(Light::LT_SPOTLIGHT);
    spotLight->setCastShadows(true);
    
    SceneNode* flashlight = mMainNode->createChildSceneNode();
    flashlight->attachObject(spotLight);
    flashlight->setDirection(0, -1, 2); // -1 y
    flashlight->getParentSceneNode()->removeChild(flashlight);
    flashlightNode = mMainNode->createChildSceneNode();
    flashlightNode->addChild(flashlight);
    flashlightNode->setPosition(Vector3(0, 6, -0.1));

    spotLight->setSpotlightRange(Degree(35), Degree(50));
}

void PlayerCharacter::setMoveTarget(int offx, int offy, int offz) {
    int tileSize = 10.0;
    targetPosition.x = round(getX() / tileSize) * tileSize + offx * tileSize;
    targetPosition.y = round(getY() / tileSize) * tileSize + offy * tileSize;
    targetPosition.z = round(getZ() / tileSize) * tileSize + offz * tileSize;
    movementFulfilled = 0.0;
}

float easeInOutQuad(float t) {
    return t < 0.5 ? 2 * std::pow(t, 2) : -1 + 2 * (2 - t) * t;
}

void PlayerCharacter::update(Real elapsedTime, OIS::Keyboard* input) {
    if (movementFulfilled >= 1.0) {
        mMainNode->setPosition(targetPosition);
        lastPosition = this->getWorldPosition();
        if (input->isKeyDown(OIS::KC_W)) {
            setMoveTarget(0, 0, -1);
        }
        if (input->isKeyDown(OIS::KC_S)) {
            setMoveTarget(0, 0, 1);
        }
        if (input->isKeyDown(OIS::KC_A)) {
            setMoveTarget(-1, 0, 0);
        }
        if (input->isKeyDown(OIS::KC_D)) {
            setMoveTarget(1, 0, 0);
        }
    }
    else {
        auto position = lastPosition + (targetPosition - lastPosition) * easeInOutQuad(movementFulfilled);
        
        mMainNode->setPosition(position);
        mMainNode->lookAt(targetPosition, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);
        mMainNode->setOrientation(-mMainNode->getOrientation());

        movementFulfilled += 0.1;
    }
}

