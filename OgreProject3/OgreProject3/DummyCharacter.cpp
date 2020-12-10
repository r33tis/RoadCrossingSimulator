#include "DummyCharacter.h"
#include <sstream>

void DummyCharacter::create(SceneManager* sceneMgr, float x, float y, float z) {

    mSceneMgr = sceneMgr;
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
    mMainNode->translate(Vector3(x, y, z));


    Image imageOgre;
    imageOgre.load("carColors.png", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    TexturePtr m_texture;
    m_texture = TextureManager::getSingletonPtr()->createManual(
        "carColors",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        TEX_TYPE_2D,
        imageOgre.getWidth(), imageOgre.getHeight(),
        0, PF_X8R8G8B8);
    m_texture->loadImage(imageOgre);

    MaterialManager& lMaterialManager = MaterialManager::getSingleton();
    MaterialPtr lMaterial = lMaterialManager.create("Car", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    lMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("carColors");

    mEntity = mSceneMgr->createEntity(mName, "Car.mesh");
    mEntity->setMaterial(lMaterial);

    mMainNode->attachObject(mEntity);
}

void DummyCharacter::update(Real elapsedTime, OIS::Keyboard* input) {
}
