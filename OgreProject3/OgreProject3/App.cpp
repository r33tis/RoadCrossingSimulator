#define _USE_MATH_DEFINES

#include "App.h"
#include <math.h>
#include "PlayerCharacter.h"
#include <OgreFrameListener.h>
#include "DummyCharacter.h"



void App::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // add resource folder to resourcegroupmanager
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources", "FileSystem");

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 15, 0);
    camNode->lookAt(Ogre::Vector3(0, 1, 0), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(1); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    scnMgr->showBoundingBoxes(true);

    this->characterHandler = &CharacterHandler::getInstance();
    this->characterHandler->init(scnMgr);
    this->characterHandler->createCharacter<PlayerCharacter>(0, 5, 2);
    this->characterHandler->createCharacter<DummyCharacter>(0, 5, 2);

    scnMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
}

void App::update(Real elapsedTime, OIS::Keyboard* keyboard) {
    this->characterHandler->update(elapsedTime, keyboard);
}
