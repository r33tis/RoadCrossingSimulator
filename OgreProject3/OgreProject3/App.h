#pragma once

#include <Ogre.h>
#include <OgreShaderGenerator.h>
#include <OgreApplicationContext.h> 
#include "PlayerCharacter.h"
#include "CharacterHandler.h"
#include "TileHandler.h"
#include "LaneHandler.h"
#include "CameraHandler.h"
#include "GameController.h"
#include "Screen.h"

enum class GameState {
	Playing,
	Lost,
	Won
};

class App : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
protected:
	PlayerCharacter* player;
	CharacterHandler* characterHandler;
	TileHandler* tileHandler;
	LaneHandler* laneHandler;
	CameraHandler* cameraHandler;
	GameController* gameController;
	OIS::InputManager* InputManager;
	OIS::Keyboard* Keyboard;
	OIS::Mouse* Mouse;
	GameState gameState;
	Screen* activeScreen;
public:
	void setup(void);
	void update(Real elapsedTime, OIS::Keyboard* keyboard, OIS::Mouse* mouse);
	static App* getInstance() {
		static App instance;
		return &instance;
	}
};