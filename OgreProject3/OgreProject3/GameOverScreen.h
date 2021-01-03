#pragma once
#include <Ogre.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreApplicationContext.h> 
#include "Screen.h"

class GameOverScreen : public Screen
{
private:
	Ogre::Overlay* canvas;
	std::vector<Ogre::MaterialPtr> screens;
	float glitchCounter;
	float nextGlitchThreshold;
public:
	GameOverScreen();
	~GameOverScreen();
	void update();
};

