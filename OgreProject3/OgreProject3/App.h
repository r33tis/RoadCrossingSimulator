#pragma once

#include <Ogre.h>
#include <OgreShaderGenerator.h>
#include <OgreApplicationContext.h> 
#include "PlayerCharacter.h"

class App : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
protected:
	PlayerCharacter* player;
	OIS::InputManager* InputManager;
	OIS::Keyboard* Keyboard;
	OIS::Mouse* Mouse;
public:
	void setup(void);
	void update(Real elapsedTime, OIS::Keyboard* keyboard);
};