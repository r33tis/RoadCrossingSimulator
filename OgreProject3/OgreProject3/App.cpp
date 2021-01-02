#define _USE_MATH_DEFINES

#include "App.h"
#include "PlayerCharacter.h"
#include "DummyCharacter.h"
#include "SpaceClamper.h"
#include <math.h>
#include <OgreFrameListener.h>
#include <OgreOverlaySystem.h>

void App::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();
    Ogre::OverlaySystem* overlaySys = OgreBites::ApplicationContext::getOverlaySystem();
    scnMgr->addRenderQueueListener(overlaySys);
    scnMgr->setShadowTextureSettings(512, 6);
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);
    scnMgr->setShadowTextureSelfShadow(true);

    // add resource folder to resourcegroupmanager
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources", "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources/environment", "FileSystem");

    // Initialise resources groups                      
    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    Ogre::ResourceGroupManager::getSingleton().loadResourceGroup(ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    /*Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 350, 15);
    lightNode->attachObject(light);*/

    scnMgr->showBoundingBoxes(false);

    float worldWidth = 120.0;
    float worldLength = 1800.0;
    float laneLength = 10.0;

    SpaceClamper::getInstance()->init(laneLength, laneLength, laneLength, SpaceClamper::clampMode::centre);

    this->tileHandler = TileHandler::getInstance();
    this->tileHandler->init(scnMgr, 10.0);
    this->tileHandler->createTiles(-worldWidth / 2.0, worldWidth / 2.0, -worldLength, 6*laneLength);

    this->characterHandler = CharacterHandler::getInstance();
    this->characterHandler->init(scnMgr);
    auto player = this->characterHandler->createCharacter<PlayerCharacter>(0, 0, SpaceClamper::getInstance()->clampZ(0.0));
    player->getMainNode()->yaw(Radian(Degree(180)));

    this->laneHandler = LaneHandler::getInstance();
    this->laneHandler->init(scnMgr, laneLength, -worldWidth/2.0, worldWidth/2.0, 0.5, 1.5, 5.0, 10.0, 3.0, 5.0);
    this->laneHandler->createLanes(worldLength / laneLength);

    this->cameraHandler = CameraHandler::getInstance();
    this->cameraHandler->init(scnMgr, player, 1.0);
    auto cam = this->cameraHandler->createCamera();
    getRenderWindow()->addViewport(cam);

    this->gameController = GameController::getInstance();
    this->gameController->init(scnMgr, player, 120.0, laneLength);
}

void App::update(Real elapsedTime, OIS::Keyboard* keyboard, OIS::Mouse* mouse) {
    this->characterHandler->update(elapsedTime, keyboard, mouse);
    this->tileHandler->update(elapsedTime);
    this->laneHandler->update(elapsedTime, keyboard, mouse);
    this->cameraHandler->update(elapsedTime, keyboard);
    this->gameController->update(elapsedTime, keyboard);
}
