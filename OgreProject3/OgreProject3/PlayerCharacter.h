#pragma once

#include "Character.h"
#include <iostream>
#include <OgreInput.h>
#include <Ogre.h>
#include "CollidableCharacter.h"

using namespace Ogre;
using namespace std;

enum class PlayerState {
    Playing,
    Lost,
    Won
};

class PlayerCharacter : public CollidableCharacter {
protected:
    Vector3 targetPosition;
    Vector3 lastPosition;
    float movementFulfilled;
    PlayerState playerState;
    AnimationState* animationState;
public:
    void create(SceneManager* mSceneMgr, float x, float y, float z);
    void setMovementBounds(float leftBound, float rightBound, float botBound, float topBound);
    void update(Real elapsedTime, OIS::Keyboard* keyboard, OIS::Mouse* mouse);
    PlayerState getPlayerState();
    void setPlayerState(PlayerState playerState);
    float leftBound;
    float rightBound;
    float botBound;
    float topBound;
private:
    void initFlashlight();
    void setMoveTarget(int x, int y, int z);
    float speed;
    float indirectSpeed;
    SceneNode* flashlightNode;
};

