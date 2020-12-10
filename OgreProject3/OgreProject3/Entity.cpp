
using namespace Ogre;

// example is from 
// http://wiki.ogre3d.org/3rd+person+camera+system+tutorial?structure=Cookbook#rd_person_camera_-_Chasing

class Entity {
    // Attributes ------------------------------------------------------------------------------
protected:
    SceneNode* mMainNode; // Main character node
    SceneNode* mSightNode; // "Sight" node - The character is supposed to be looking here
    SceneNode* mCameraNode; // Node for the chase camera
    Entity* mEntity; // Character entity
    SceneManager* mSceneMgr;
public:
    // Methods ---------------------------------------------------------------------------------
protected:
public:
    // Updates the character (movement...)
    virtual void update(Real elapsedTime, OIS::Keyboard* input) = 0;
    // The three methods below returns the two camera-related nodes, 
    // and the current position of the character (for the 1st person camera)
    SceneNode* getSightNode() {
        return mSightNode;
    }
    SceneNode* getCameraNode() {
        return mCameraNode;
    }
    Vector3 getWorldPosition() {
        return mMainNode->_getDerivedPosition();
    }
};