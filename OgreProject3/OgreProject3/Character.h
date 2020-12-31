#pragma once

#include <Ogre.h>
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISInputManager.h>
#include <iostream>
#include <sstream>

using namespace Ogre;

class Character {
    // Attributes ------------------------------------------------------------------------------
protected:
    SceneNode* mMainNode; // Main character node
    Entity* mEntity; // Character entity
    SceneManager* mSceneMgr;
    String mName; // ogre requires a name for scene nodes
public:
    Character() {}
    ~Character() {
        mMainNode->detachAllObjects();
        delete mEntity;
        mMainNode->removeAndDestroyAllChildren();
        mSceneMgr->destroySceneNode(mName);
    }
    void _setName(const char* mName) {
        std::ostringstream oss;
        oss << "char_" << mName;
        this->mName = oss.str().c_str();
        std::cout << "created character with name " << this->mName << "\n";
    }
    virtual void create(SceneManager* mSceneMgr, float x, float y, float z) = 0;
    virtual void update(Real elapsedTime, OIS::Keyboard* input) = 0;
    Vector3 getWorldPosition() {
        return mMainNode->_getDerivedPosition();
    }
    AxisAlignedBox getBbox() {
        return this->mMainNode->_getWorldAABB();
    }
    float getX();
    float getY();
    float getZ();
    SceneNode* getMainNode();
    void loadModel(const char* meshName, const char* textureName);
};