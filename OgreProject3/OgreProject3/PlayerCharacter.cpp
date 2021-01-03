#include "PlayerCharacter.h"
#include "DummyCharacter.h"
#include <OgreLight.h>
#include <sstream>
#include "Car.h"
#include "App.h"

void PlayerCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->playerState = PlayerState::Playing;

    this->loadModel("Student", "studentColors.png");
    mEntity->setCastShadows(true);
    auto mAnimationState = mEntity->getAnimationState("Walk");
    mAnimationState->setWeight(1);
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

    this->speed = 20.0;
    this->indirectSpeed = 10.0;

    this->initFlashlight();

    targetPosition = Vector3(x, y, z);
    lastPosition = Vector3(x, y, z);
    movementFulfilled = 0.0;
}

void PlayerCharacter::init(float leftBound, float rightBound, float botBound, float topBound) {
    this->leftBound = leftBound;
    this->rightBound = rightBound;
    this->botBound = botBound;
    this->topBound = topBound;
}

void PlayerCharacter::initFlashlight() {
    Light* ambientLight = this->mSceneMgr->createLight("ambientLight");
    ambientLight->setDiffuseColour(0.09, 0.085, 0.08);
    ambientLight->setSpecularColour(0.09, 0.085, 0.08);
    ambientLight->setType(Light::LT_POINT);
    ambientLight->setCastShadows(false);
    ambientLight->setRenderingDistance(5.0);
    ambientLight->setAttenuation(15.0, 0, 1.0, 1.1);

    Light* spotLight = this->mSceneMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(0.9, 0.85, 0.8);
    spotLight->setSpecularColour(0.9, 0.85, 0.8);
    spotLight->setType(Light::LT_SPOTLIGHT);
    spotLight->setCastShadows(true);
    
    SceneNode* flashlight = mMainNode->createChildSceneNode();
    flashlight->attachObject(spotLight);
    flashlight->attachObject(ambientLight);
    flashlight->setDirection(0, -1, 2); // -1 y
    flashlight->getParentSceneNode()->removeChild(flashlight);
    flashlightNode = mMainNode->createChildSceneNode();
    flashlightNode->addChild(flashlight);
    flashlightNode->setPosition(Vector3(0, 10, 0));

    spotLight->setSpotlightRange(Degree(45), Degree(60));
}

void PlayerCharacter::setMoveTarget(int offx, int offy, int offz) {
    int tileSize = 10.0;
    targetPosition.x = round(getX() / tileSize) * tileSize + offx * tileSize;
    targetPosition.y = round(getY() / tileSize) * tileSize + offy * tileSize;
    targetPosition.z = round(getZ() / tileSize) * tileSize + offz * tileSize;

    if (targetPosition.x < leftBound ||
        targetPosition.x > rightBound ||
        targetPosition.z < topBound ||
        targetPosition.z > botBound)
    {
        targetPosition = lastPosition;
    } else {
        movementFulfilled = 0.0;
    }

}

float easeInOutQuad(float t) {
    return t < 0.5 ? 2.0 * std::pow(t, 2.0) : -1.0 + 2.0 * (2.0 - t) * t;
}


void PlayerCharacter::update(Real elapsedTime, OIS::Keyboard* keyboard, OIS::Mouse* mouse) {
    if (playerState == PlayerState::Playing) {
        // Cheat ahead
        if (movementFulfilled >= 0.7) {
            mMainNode->setPosition(targetPosition);
            lastPosition = this->getWorldPosition();
            if (keyboard->isKeyDown(OIS::KC_W)) {
                setMoveTarget(0, 0, -1);
            }
            if (keyboard->isKeyDown(OIS::KC_S)) {
                setMoveTarget(0, 0, 1);
            }
            if (keyboard->isKeyDown(OIS::KC_A)) {
                setMoveTarget(-1, 0, 0);
            }
            if (keyboard->isKeyDown(OIS::KC_D)) {
                setMoveTarget(1, 0, 0);
            }
        }
        else {
            auto state = mEntity->getAnimationState("Walk");
            state->addTime(0.1);
            auto position = lastPosition + (targetPosition - lastPosition) * easeInOutQuad(movementFulfilled);
            position.y = (0.5 - std::abs(0.5 - easeInOutQuad(movementFulfilled))) * 4.0;

            mMainNode->setPosition(position);
            auto lookAtPosition = targetPosition;
            lookAtPosition.y = position.y;

            Quaternion o = flashlightNode->_getDerivedOrientation();
            mMainNode->lookAt(lookAtPosition, Ogre::Node::TS_WORLD, -Ogre::Vector3::UNIT_Z);
            flashlightNode->_setDerivedOrientation(o);

            movementFulfilled += 0.15;
        }

        int shiftX = mouse->getMouseState().X.rel;
        flashlightNode->yaw(Radian(-shiftX * elapsedTime * 0.1));

        if (this->placeMeeting<Car>(0, 0)) {
            std::cout << "PLAYER DIED!\n";
            playerState = PlayerState::Lost;
        }
    }
}

PlayerState PlayerCharacter::getPlayerState()
{
    return playerState;
}

void PlayerCharacter::setPlayerState(PlayerState playerState)
{
    if (playerState == PlayerState::Playing) {
        auto newPos = Vector3(0, 0, SpaceClamper::getInstance()->clampZ(0.0));
        this->setWorldPosition(newPos);
        this->targetPosition = newPos;
        this->lastPosition = newPos;
    }
    this->playerState = playerState;
}

