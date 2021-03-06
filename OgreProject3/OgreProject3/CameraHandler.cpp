#include "CameraHandler.h"
#include "PlayerCharacter.h"
#include "Character.h"
#include "Car.h"

void CameraHandler::init(SceneManager* sceneMgr, Character* quarry, float speed)
{
	this->t = 0.0;
	this->speed = speed;
	this->quarry = quarry;
	this->sceneMgr = sceneMgr;
	this->offSet = Vector3(30.0, 30.0, 30.0);
	this->offSet2 = Vector3(-45.0, 30.0, 45.0);
}

void CameraHandler::update(Real elapsedTime, OIS::Keyboard* input) {
	
	if (t >= 0.0 && t <= 1.0) {
        t += elapsedTime;
		Vector3 position = quarry->getWorldPosition();
        camNode->setPosition(position + this->offSet);
		lightNode->setPosition(position + this->offSet2);
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

	PlayerCharacter* pc = static_cast<PlayerCharacter*>(quarry);
	Ogre::Real distance = pc->distance<Car>(pc->getWorldPosition());
	Ogre::Real cap = 50.0;
	if (distance > cap) {
		distance = cap;
	}
	float t = (std::sinf((distance / cap) * 3.14f - 1.57f) + 1) * 0.5f;
	float r = 1.0 - t;
	if (r < 0.0) { r = 0.0; }
	if (r > 1.0) { r = 1.0; }
	float b = 0.5;
	if (b < 0.0) { b = 0.0; }
	if (b > 1.0) { b = 1.0; }
	float g = t;
	if (g < 0.0) { g = 0.0; }
	if (g > 1.0) { g = 1.0; }
	spotLight->setDiffuseColour(r, g, b);
	spotLight->setSpecularColour(r, g, b);
}

// https://forums.ogre3d.org/viewtopic.php?f=2&t=26244&start=4
Matrix4 BuildScaledOrthoMatrix(float left, float right, float bottom, float top, float near, float far)
{
	float invw = 1 / (right - left);
	float invh = 1 / (top - bottom);
	float invd = 1 / (far - near);

	Matrix4 proj = Matrix4(
		2 * invw, 0, 0, -(right + left) * invw,
		0, 2 * invh, 0, -(top + bottom) * invh,
		0, 0, -2 * invd, -(far + near) * invd,
		0, 0, 0, 1
	);

	return proj;
}

Camera* CameraHandler::createCamera() {
	camNode = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(this->offSet);
	camNode->lookAt(Vector3(0, 1, 0), Ogre::Node::TS_PARENT);

	lightNode = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(this->offSet2);
	lightNode->lookAt(Vector3(0, 1, 0), Ogre::Node::TS_PARENT);
	spotLight = this->sceneMgr->createLight("CameraSpotLight");
	spotLight->setDiffuseColour(0.8, 0.1, 0.1);
	spotLight->setSpecularColour(0.8, 0.1, 0.1);
	spotLight->setType(Light::LT_SPOTLIGHT);
	spotLight->setCastShadows(true);
	lightNode->attachObject(spotLight);
	spotLight->setSpotlightRange(Degree(9), Degree(12));

	Ogre::Camera* cam = sceneMgr->createCamera("myCam");
	cam->setNearClipDistance(1);
	cam->setAutoAspectRatio(true);
	if (true) {
		cam->setProjectionType(ProjectionType::PT_ORTHOGRAPHIC);
		float scale = 20.0f; // Your scale here.
		float w = cam->getOrthoWindowWidth();
		float h = cam->getOrthoWindowHeight();
		Matrix4 p = BuildScaledOrthoMatrix(w / scale / -2.0f,
			w / scale / 2.0f,
			h / scale / -2.0f,
			h / scale / 2.0f, 0, 1000);
		cam->setCustomProjectionMatrix(true, p);
	}
	camNode->attachObject(cam);
	return cam;
}