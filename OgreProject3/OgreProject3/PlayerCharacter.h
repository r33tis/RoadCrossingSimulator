#pragma once

#include "Character.h"
#include <iostream>
#include <OgreInput.h>
#include <Ogre.h>
#include "CollidableCharacter.h"

using namespace Ogre;
using namespace std;

class PlayerCharacter : public CollidableCharacter {
protected:
    Vector3 targetPosition;
    Vector3 lastPosition;
    float movementFulfilled;
    float leftBound;
    float rightBound;
    float botBound;
    float topBound;
public:
    void create(SceneManager* mSceneMgr, float x, float y, float z);
    void update(Real elapsedTime, OIS::Keyboard* keyboard, OIS::Mouse* mouse);
    void init(float leftBound, float rightBound, float botBound, float topBound);
private:
    void initFlashlight();
    void setMoveTarget(int x, int y, int z);
    float speed;
    float indirectSpeed;
    SceneNode* flashlightNode;
};

