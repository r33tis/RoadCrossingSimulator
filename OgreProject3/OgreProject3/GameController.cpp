#include "GameController.h"
#include <iostream>
#include <tgmath.h>


void GameController::init(SceneManager* sceneMgr, Character* quarry, float endTime, float laneLength) {
	this->time = 0.0;
	this->endTime = endTime;
	this->ticker = 0.0;
	this->laneLength = laneLength;
	this->bestDistance = 0;
	this->quarry = quarry;
	this->sceneMgr = sceneMgr;
	this->canvas = OverlayManager::getSingleton().create("canvas");
	this->sky = this->sceneMgr->createLight("DirectionalLight");
	this->sky->setType(Light::LT_DIRECTIONAL);
	this->sky->setCastShadows(true);
	this->sky->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	this->sky->setSpecularColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	this->skyNode = this->sceneMgr->getRootSceneNode()->createChildSceneNode();
	this->skyNode->attachObject(this->sky);
	this->skyNode->setDirection(Vector3(0, -1, 0));
	this->sixDis = std::uniform_int_distribution<>(0, 5);
	
	initNumbers();
	updateSky(0);
	
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	// Create an overlay
	this->canvas = overlayManager.create("OverlayName");
}

void GameController::reset() {
	std::cout << "reseting sky!\n";
	
	updateSky(-time);
	this->skyNode->resetOrientation();
	this->skyNode->setDirection(Vector3(0, -1, 0));

	this->time = 0.0;
	this->bestDistance = 0.0;
	updateScore(0);
}

void GameController::initNumbers() {
	auto textureManager = TextureManager::getSingletonPtr();

	for (int v = 0; v < 6; v++) {
		for (int n = 0; n < 10; n++) {
			auto name = "number" + std::to_string(v) + std::to_string(n);
			auto textureName = name + ".png";
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

			MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
			mat->getTechnique(0)->getPass(0)->createTextureUnitState(textureName);
			mat->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(1.0, 1.0, 1.0, 1.0));
			mat->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);
			mat->getTechnique(0)->getPass(0)->setTextureFiltering(TFO_NONE);
			mat->setColourWriteEnabled(true);

			numberMaterials[v][n] = mat;
		}
	}	
}

void GameController::update(Real elapsedTime, OIS::Keyboard* keyboard) {
	Ogre::Real mod = 1.0;
	
	if (keyboard->isKeyDown(OIS::KC_0)) {
		mod = 20.0;
	}
	
	time += elapsedTime * mod;
	ticker -= elapsedTime;

	//TODO: Replace score with UI and stop printing out time.
	//std::cout << "Time: "<< time << "/" << endTime << "\t" << "Score: " << bestDistance << "\n";

	int distance = (-quarry->getZ() / laneLength);
	if (distance > bestDistance) {
		bestDistance = distance;
		updateScore(bestDistance);
	}

	updateSky(elapsedTime * mod);

	if (ticker <= 0.3) {
		updateScore(bestDistance);
	}
	if (ticker <= 0.0) {
		float v = (endTime - time) / endTime;
		if (v < 0.0) { v = 0.0; }
		else if (v > 1.0) { v = 1.0; }
		ticker = v * 5;
	}
}

void GameController::updateSky(Real elapsedTime) {
	float v = (endTime - time) / endTime;
	if (v < 0.0) { v = 0.0; }
	else if (v > 1.0) { v = 1.0; }
	else {
		float shift = elapsedTime * 100 / endTime * 0.5;
		this->skyNode->pitch(Radian(Degree(shift)));
		this->skyNode->roll(Radian(Degree(shift)));
		this->skyNode->yaw(Radian(Degree(shift)));
	}

	//TODO: Different bands of light die down at different rates, so we get a cool sunset.
	//float r = 1.0 * pow(sin(v * 1.57), 0.2);
	//float g = 1.0 * pow(sin(v * 1.57), 2.0);
	//float b = 0.5 * pow(sin(v * 3.14 - 2.7), 1.0) + 0.5;
	v *= 1.5;
	float r = 0.5 * pow(sin(v * 3.14 - 1.0), 1.0) + 0.5;
	if (v > 0.8187) { r = 1.0; }
	float g = 0.5 * pow(sin(v * 3.14 - 1.9), 1.0) + 0.5;
	if (v > 1.1053) { g = 1.0; }
	float b = 0.5 * pow(sin(v * 3.14 - 2.7), 1.0) + 0.5;
	if (v > 1.3601) { b = 1.0; }
	float w = 0.3 * pow(sin(v * 1.57 - 1.57), 1.0) + 0.3;
	if (v > 2.0005) { w = 0.6; }

	this->sceneMgr->setAmbientLight(Ogre::ColourValue(w, w, w));
	this->sky->setDiffuseColour(Ogre::ColourValue(r, g, b));
	this->sky->setSpecularColour(Ogre::ColourValue(r, g, b));
}

void GameController::updateScore(int distance) {
	int total = distance;

	int order = 1;
	while (order <= total) {
		order *= 10;
	}

	if (total == 0) {
		numbers.push(0);
	}

	int orderFloor = order / 10;
	while (orderFloor >= 1) {
		int counter = 0;
		while (total >= orderFloor) {
			total -= orderFloor;
			counter++;
		}
		numbers.push(counter);
		orderFloor /= 10;
	}

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	float scale = 2.0;
	float width = (16 * scale) / overlayManager.getViewportWidth();
	float height = (32 * scale) / overlayManager.getViewportHeight();
	float paddingX = ((width + height) / 2) * (0.5) + (sixDis(gen) * scale) / overlayManager.getViewportWidth();
	float paddingY = ((width + height) / 2) * (0.5) + (sixDis(gen) * scale) / overlayManager.getViewportWidth();

	int i = 0;
	canvas->clear();
	while (!numbers.empty()) {
		int number = numbers.top();
		int version = sixDis(gen);

		std::string name = "Panel" + std::to_string(i) + "_" + std::to_string(number) + "_" + std::to_string(version);
		
		Ogre::OverlayContainer* panel;
		if (overlayManager.hasOverlayElement(name)) {
			panel = static_cast<Ogre::OverlayContainer*>(overlayManager.getOverlayElement(name));
		}
		else {
			panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", name));
		}
		
		
		panel->setPosition(1.0 - width * (i + 1) - paddingX, 0.0 + paddingY);
		panel->setDimensions(width, height);
		panel->setMaterial(numberMaterials[version][number]);
		canvas->add2D(panel);

		// Show the overlay
		

		i++;
		numbers.pop();
	}
	canvas->show();

	
}