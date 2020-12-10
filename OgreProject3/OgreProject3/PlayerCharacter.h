#pragma once

#include "Character.h"
#include <iostream>
#include <OgreInput.h>
#include <Ogre.h>
#include "CollidableCharacter.h"

using namespace Ogre;
using namespace std;

class PlayerCharacter : public CollidableCharacter {
public:
    void create(SceneManager* mSceneMgr, float x, float y, float z);
    void update(Real elapsedTime, OIS::Keyboard* input);
};
