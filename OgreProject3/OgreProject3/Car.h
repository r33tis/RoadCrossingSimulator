#pragma once

#include "Character.h"
#include <iostream>
#include <Ogre.h>
#include "CollidableCharacter.h"

using namespace Ogre;

class Car : public CollidableCharacter {
private:
    float speed;
public:
    void create(SceneManager* mSceneMgr, float x, float y, float z);
    void update(Real elapsedTime, OIS::Keyboard* input);
    void setSpeed(float speed);
    //Real x();
};

