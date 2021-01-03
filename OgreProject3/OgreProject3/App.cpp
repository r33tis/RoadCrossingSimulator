#define _USE_MATH_DEFINES

#include "App.h"
#include "PlayerCharacter.h"
#include "DummyCharacter.h"
#include "SpaceClamper.h"
#include <math.h>
#include <OgreFrameListener.h>
#include <OgreOverlaySystem.h>
#include "GameOverScreen.h"

void App::setup(void)
{
    gameState = GameState::Playing;
    activeScreen = NULL;

    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();
    Ogre::OverlaySystem* overlaySys = OgreBites::ApplicationContext::getOverlaySystem();
    scnMgr->addRenderQueueListener(overlaySys);
    scnMgr->setShadowTextureSettings(2048, 6);
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);
    scnMgr->setShadowTextureSelfShadow(true);

    // add resource folder to resourcegroupmanager
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources", "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources/environment", "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources/screens", "FileSystem");

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

    float dayTime = 160.0;
    float worldWidth = 240.0;
    float worldLength = 1200.0;
    float laneLength = 10.0;

    SpaceClamper::getInstance()->init(laneLength, laneLength, laneLength, SpaceClamper::clampMode::centre);

    this->tileHandler = TileHandler::getInstance();
    this->tileHandler->init(scnMgr, 10.0);
    this->tileHandler->createTiles(-worldWidth / 2.0, worldWidth / 2.0, -worldLength, 6*laneLength);

    this->characterHandler = CharacterHandler::getInstance();
    this->characterHandler->init(scnMgr);

    this->player = (PlayerCharacter*) this->characterHandler->createCharacter<PlayerCharacter>(0, 0, 0);
    //this->player->getMainNode()->yaw(Radian(Degree(180)));
    this->player->setMovementBounds(-worldWidth / 2.0, worldWidth / 2.0, laneLength, -worldLength);

    this->laneHandler = LaneHandler::getInstance();
    this->laneHandler->init(scnMgr, laneLength, -worldWidth / 2.0, worldWidth / 2.0, 0.5, 1.5, 4.0, 8.0, 1, 10);
    this->laneHandler->createLanes(worldLength / laneLength);

    this->cameraHandler = CameraHandler::getInstance();
    this->cameraHandler->init(scnMgr, player, 1.0);
    auto cam = this->cameraHandler->createCamera();
    getRenderWindow()->addViewport(cam);

    this->gameController = GameController::getInstance();
    this->gameController->init(scnMgr, player, dayTime, laneLength);

}

void App::update(Real elapsedTime, OIS::Keyboard* keyboard, OIS::Mouse* mouse) {
    
    

    if (gameState == GameState::Playing) {
        if (player->getPlayerState() == PlayerState::Lost) {
            gameState = GameState::Lost;
            activeScreen = new GameOverScreen();
        }
        else if (player->getPlayerState() == PlayerState::Won) {
            gameState = GameState::Won;
        }
        this->characterHandler->update(elapsedTime, keyboard, mouse);
        this->tileHandler->update(elapsedTime);
        this->laneHandler->update(elapsedTime, keyboard, mouse);
        this->cameraHandler->update(elapsedTime, keyboard);
        this->gameController->update(elapsedTime, keyboard);
    }
    else if (gameState == GameState::Lost) {
        if (keyboard->isKeyDown(OIS::KC_SPACE)) {
            player->setPlayerState(PlayerState::Playing);
            gameController->reset();
            if (activeScreen) {
                std::cout << "deleting active screen!\n";
                delete activeScreen;
            }
            activeScreen = NULL;
            gameState = GameState::Playing;
        }
    }
    if (activeScreen) {
        activeScreen->update();
    }
}
