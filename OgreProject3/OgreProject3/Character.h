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
    Character() {
        std::ostringstream oss;
        oss << "char_" << (long) this;
        mName = oss.str().c_str();
        std::cout << "created character with name " << mName << "\n";
    }
    ~Character() {
        mMainNode->detachAllObjects();
        delete mEntity;
        mMainNode->removeAndDestroyAllChildren();
        mSceneMgr->destroySceneNode(mName);
    }
    virtual void create(SceneManager* mSceneMgr, float x, float y, float z) = 0;
    virtual void update(Real elapsedTime, OIS::Keyboard* input) = 0;
    Vector3 getWorldPosition() {
        return mMainNode->_getDerivedPosition();
    }
    AxisAlignedBox getBbox() {
        return this->mMainNode->_getWorldAABB();
    }
};




