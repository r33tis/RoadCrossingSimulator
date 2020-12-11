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
    /*Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 350, 15);
    lightNode->attachObject(light);*/

    scnMgr->showBoundingBoxes(true);

    this->tileHandler = TileHandler::getInstance();
    this->tileHandler->init(scnMgr);
    this->tileHandler->createTiles(-50, 50, -50, 50, 10.0);

    this->characterHandler = CharacterHandler::getInstance();
    this->characterHandler->init(scnMgr);
    auto player = this->characterHandler->createCharacter<PlayerCharacter>(0, 5, 2);

    this->characterHandler->createCharacter<DummyCharacter>(0, 5, 2);

    this->laneHandler = LaneHandler::getInstance();
    this->laneHandler->init(scnMgr, 10.0, -15, 15, 0.5, 1.5, 5.0, 10.0);
    this->laneHandler->createLanes(10);

    this->cameraHandler = CameraHandler::getInstance();
    this->cameraHandler->init(scnMgr, player, 1.0);
    auto cam = this->cameraHandler->createCamera();
    getRenderWindow()->addViewport(cam);

    this->gameController = GameController::getInstance();
    this->gameController->init(scnMgr, player, 90.0);
}

void App::update(Real elapsedTime, OIS::Keyboard* keyboard) {
    this->characterHandler->update(elapsedTime, keyboard);
    this->tileHandler->update(elapsedTime);
    this->laneHandler->update(elapsedTime, keyboard);
    this->cameraHandler->update(elapsedTime, keyboard);
    this->gameController->update(elapsedTime, keyboard);
}
