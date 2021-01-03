#include "Screen.h"
#include <iostream>

using namespace Ogre;

Screen::Screen()
{
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	glitchCounter = 0.0;
	nextGlitchThreshold = 5.0;

	std::cout << "CANVAS INIT JHAHAHA\n";

	this->canvas = overlayManager.create("gameOverScreen");
}


Screen::~Screen()
{
	this->canvas->clear();
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	overlayManager.destroy("gameOverScreen");
}

void Screen::update()
{
	canvas->clear();
	std::string name = "GameOverImage";
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	float scale = 2.0;
	float width = (320 * scale) / overlayManager.getViewportWidth();
	float height = (240 * scale) / overlayManager.getViewportHeight();

	Ogre::OverlayContainer* panel;
	if (overlayManager.hasOverlayElement(name)) {
		panel = static_cast<Ogre::OverlayContainer*>(overlayManager.getOverlayElement(name));
	}
	else {
		panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", name));
	}


	std::vector<MaterialPtr>::iterator randIt = screens.begin();
	if (glitchCounter >= nextGlitchThreshold) {
		std::advance(randIt, std::rand() % screens.size());
	}
	if (glitchCounter >= nextGlitchThreshold + 2.0) {
		glitchCounter = 0.0;
		nextGlitchThreshold = 3.5 + std::rand() % 17;
	}

	panel->setDimensions(width, height);
	panel->setPosition(
		(overlayManager.getViewportWidth() - 320 * scale) / 2 / overlayManager.getViewportWidth(),
		(overlayManager.getViewportHeight() - 240 * scale) / 2 / overlayManager.getViewportHeight()
	);
	panel->setMaterial(*randIt);
	canvas->add2D(panel);
	canvas->show();

	glitchCounter += 0.7;
}

void Screen::loadScreens(std::vector<std::string> fileNames)
{
	auto textureManager = TextureManager::getSingletonPtr();
	auto materialManager = Ogre::MaterialManager::getSingletonPtr();

	for (auto name : fileNames) {
		auto textureName = name + ".png";

		if (!materialManager->resourceExists(name)) {
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

			MaterialPtr mat = materialManager->create(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
			mat->getTechnique(0)->getPass(0)->createTextureUnitState(textureName);
			mat->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(1.0, 1.0, 1.0, 1.0));
			mat->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);
			mat->getTechnique(0)->getPass(0)->setTextureFiltering(TFO_NONE);
			mat->setColourWriteEnabled(true);

			screens.push_back(mat);
		}
		else {
			screens.push_back(materialManager->getByName(name));
		}
	}
}
