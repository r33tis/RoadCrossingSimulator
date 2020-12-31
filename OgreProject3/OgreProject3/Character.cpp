#include "Character.h"
#include <iostream>

using namespace std;

float Character::getX()
{
	return this->mMainNode->getPosition().x;
}

float Character::getY()
{
	return this->mMainNode->getPosition().y;
}

float Character::getZ()
{
	return this->mMainNode->getPosition().z;
}

SceneNode* Character::getMainNode()
{
    return mMainNode;
}

void Character::loadModel(const char* meshName, const char* textureName) {
    auto textureManager = TextureManager::getSingletonPtr();
    MaterialManager& lMaterialManager = MaterialManager::getSingleton();
    
    if (!lMaterialManager.resourceExists(meshName)) {

        Image imageOgre;
        imageOgre.load(textureName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        TexturePtr m_texture;
        m_texture = textureManager->createManual(
            textureName,
            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            TEX_TYPE_2D,
            imageOgre.getWidth(), imageOgre.getHeight(),
            0, PF_X8R8G8B8);
        m_texture->loadImage(imageOgre);

        
        MaterialPtr lMaterial = lMaterialManager.create(meshName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        lMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(textureName);
        lMaterial->setReceiveShadows(false);
    }
    std::string buf(meshName);
    buf.append(".mesh");

    mEntity = mSceneMgr->createEntity(mName, buf);
    mEntity->setMaterialName(meshName);
    mEntity->setCastShadows(true);
    
    mMainNode->attachObject(mEntity);
}