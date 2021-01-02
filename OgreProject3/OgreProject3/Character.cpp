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
    
    std::string buf(meshName);
    buf.append(".mesh");

    mEntity = mSceneMgr->createEntity(mName, buf);
    mEntity->setMaterialName(meshName);
    
    mMainNode->attachObject(mEntity);
}