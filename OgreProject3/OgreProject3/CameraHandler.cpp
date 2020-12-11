#include "CameraHandler.h"

void CameraHandler::init(SceneManager* sceneMgr, Character* quarry, float speed)
{
	this->t = 0.0;
	this->speed = speed;
	this->quarry = quarry;
	this->sceneMgr = sceneMgr;
}

void CameraHandler::update(Real elapsedTime, OIS::Keyboard* input) {
	if (t >= 0.0 && t <= 1.0) {
        t += elapsedTime;
        Vector3 position = quarry->getWorldPosition();
        Vector3 offset = Vector3(0, 35, 15);
        camNode->setPosition(position + offset);
    }

	if (
		input->isKeyDown(OIS::KC_W) ||
		input->isKeyDown(OIS::KC_S) ||
		input->isKeyDown(OIS::KC_A) ||
		input->isKeyDown(OIS::KC_D)
	)
	{
		lastPoint = camNode->getPosition();
		t = 0.0;
	}
}

Camera* CameraHandler::createCamera() {
	camNode = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 35, 15);
	camNode->lookAt(Ogre::Vector3(0, 1, 0), Ogre::Node::TS_PARENT);

	Ogre::Camera* cam = sceneMgr->createCamera("myCam");
	cam->setNearClipDistance(1);
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	return cam;
}