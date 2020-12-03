#pragma once

#include "Character.h"
#include <iostream>
#include <OgreInput.h>
#include <Ogre.h>

using namespace Ogre;
using namespace std;

// Specialization of the Character class - Our dear Ogre :D
class PlayerCharacter : public Character {
    // Attributes ------------------------------------------------------------------------------
protected:
    String mName;
public:
    PlayerCharacter(String name, SceneManager* sceneMgr);
    ~PlayerCharacter();

    void update(Real elapsedTime, OIS::Keyboard* input);
};