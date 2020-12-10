#include "PlayerCharacter.h"
#include <sstream>
#include "DummyCharacter.h"

void PlayerCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {
    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));


    Image imageOgre;
    imageOgre.load("studentColors.PNG", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    TexturePtr m_texture;
    m_texture = TextureManager::getSingletonPtr()->createManual(
        "studentColors",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        TEX_TYPE_2D,
        imageOgre.getWidth(), imageOgre.getHeight(),
        0, PF_X8R8G8B8);
    m_texture->loadImage(imageOgre);

    MaterialManager& lMaterialManager = MaterialManager::getSingleton();
    MaterialPtr lMaterial = lMaterialManager.create("Cube", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    lMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("studentColors");

    mEntity = mSceneMgr->createEntity(mName, "Cube.mesh");
    mEntity->setMaterial(lMaterial);
    
 
    mMainNode->attachObject(mEntity);
}

void PlayerCharacter::update(Real elapsedTime, OIS::Keyboard* input) {
    if (this->placeMeeting<DummyCharacter>(0, 0)) {
        mMainNode->setScale(Vector3(1.5, 1.5, 1.5));
        cout << "collision!";
    }
    else {
        mMainNode->setScale(Vector3(1, 1, 1));
    }

    if (input->isKeyDown(OIS::KC_W)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, 5 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_S)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, -3 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_A)) {
        mMainNode->yaw(Radian(2 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_D)) {
        mMainNode->yaw(Radian(-2 * elapsedTime));
    }
}

