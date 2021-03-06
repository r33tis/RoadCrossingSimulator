#include "PlayerCharacter.h"
#include "DummyCharacter.h"
#include <OgreLight.h>
#include <sstream>
#include "Car.h"

void PlayerCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));

    this->loadModel("Cube", "studentColors.png");
    mEntity->setCastShadows(true);
    animationState = mEntity->getAnimationState("Walk");
    animationState->setWeight(1);
    animationState->setLoop(true);
    animationState->setEnabled(true);

    this->speed = 20.0;
    this->indirectSpeed = 10.0;

    this->initFlashlight();

    targetPosition = Vector3(x, y, z);
    lastPosition = Vector3(x, y, z);
    movementFulfilled = 0.0;
}

void PlayerCharacter::setMovementBounds(float leftBound, float rightBound, float botBound, float topBound) {
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

    std::cout << targetPosition.x << " " << targetPosition.y << " " << targetPosition.z << "\n";

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
    auto animation = animationState->getAnimationName();

    if (movementFulfilled >= 1.0) {
        animation = "Walk";
    }

    if (movementFulfilled >= 0.7) {
        mMainNode->setPosition(targetPosition);
        lastPosition = this->getWorldPosition();
        if (keyboard->isKeyDown(OIS::KC_W)) {
            setMoveTarget(0, 0, -1);
            animation = "Walk";
        }
        if (keyboard->isKeyDown(OIS::KC_S)) {
            setMoveTarget(0, 0, 1);
            animation = "Walk";
        }
        if (keyboard->isKeyDown(OIS::KC_A)) {
            setMoveTarget(-1, 0, 0);
            animation = "Jump";
        }
        if (keyboard->isKeyDown(OIS::KC_D)) {
            setMoveTarget(1, 0, 0);
            animation = "Jump";
        }
    }
    if (animationState->getAnimationName() != animation) {
        animationState->setWeight(0);
        animationState = mEntity->getAnimationState(animation);
        animationState->setWeight(1);
        animationState->setLoop(true);
        animationState->setEnabled(true);
        animationState->setTimePosition(0);
    }
    if (movementFulfilled <= 1.0) {
        auto position = lastPosition + (targetPosition - lastPosition) * easeInOutQuad(movementFulfilled);
        if (animation == "Jump") {
            position.y = (0.5 - std::abs(0.5 - easeInOutQuad(movementFulfilled))) * 4.0;
        }
        else {
            position.y = (0.5 - std::abs(0.5 - easeInOutQuad(movementFulfilled)));
        }
        
        
        mMainNode->setPosition(position);
        auto lookAtPosition = targetPosition;
        lookAtPosition.y = position.y;

        Quaternion o = flashlightNode->_getDerivedOrientation();
        mMainNode->lookAt(lookAtPosition, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);
        flashlightNode->_setDerivedOrientation(o);

        movementFulfilled += elapsedTime * 2;
        animationState->addTime(elapsedTime * 2);
    }
    
    int shiftX = mouse->getMouseState().X.rel;
    flashlightNode->yaw(Radian(-shiftX * elapsedTime * 0.1));

    if (playerState == PlayerState::Playing && this->placeMeeting<Car>(0, 0)) {
        std::cout << "PLAYER DIED!\n";
        playerState = PlayerState::Lost;
    }
    if (playerState == PlayerState::Playing && this->getZ() <= topBound) {
        std::cout << "PLAYER WON!\n";
        playerState = PlayerState::Won;
    }
}

PlayerState PlayerCharacter::getPlayerState()
{
    return playerState;
}

void PlayerCharacter::setPlayerState(PlayerState playerState)
{
    this->playerState = playerState;
    if (playerState == PlayerState::Playing) {
        auto newPos = Vector3(0, 0, 0);
        this->setWorldPosition(newPos);
        this->targetPosition = newPos;
        this->lastPosition = newPos;
    }
    this->playerState = playerState;
}