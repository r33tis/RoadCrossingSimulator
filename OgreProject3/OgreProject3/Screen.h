#pragma once
#include <Ogre.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreApplicationContext.h> 

class Screen
{
protected:
	Ogre::Overlay* canvas;
	std::vector<Ogre::MaterialPtr> screens;
	float glitchCounter;
	float nextGlitchThreshold;
public:
	Screen();
	void loadScreens(std::vector<std::string> fileNames);
	void update();
	~Screen();
};

