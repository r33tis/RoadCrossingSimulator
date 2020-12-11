#pragma once

#include <Ogre.h>
#include <OgreShaderGenerator.h>
#include <OgreApplicationContext.h> 
#include "PlayerCharacter.h"
#include "CharacterHandler.h"
#include "TileHandler.h"

class App : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
protected:
	CharacterHandler* characterHandler;
	TileHandler* tileHandler;
	OIS::InputManager* InputManager;
	OIS::Keyboard* Keyboard;
	OIS::Mouse* Mouse;
public:
	void setup(void);
	void update(Real elapsedTime, OIS::Keyboard* keyboard);
};