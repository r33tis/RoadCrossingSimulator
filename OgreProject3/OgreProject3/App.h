#include <Ogre.h>
#include <OgreShaderGenerator.h>
#include <OgreApplicationContext.h> 
#include <OgreFrameListener.h>
#include <iostream>

class App
	: public OgreBites::ApplicationContext
	, public OgreBites::InputListener
	, public Ogre::FrameListener
{
	void App::setup(void);
	
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool textInput(const OgreBites::TextInputEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
};