#include "TileHandler.h"
#include "SpaceClamper.h"
#include <iostream>

void TileHandler::init(SceneManager* sceneMgr, float tileSize) {
	this->sceneMgr = sceneMgr;
	this->tiles = std::vector<Ogre::SceneNode*>();

	this->tileMaterial = Ogre::MaterialManager::getSingleton().create("tile material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
	//this->tileMaterial->getTechnique(0)->getPass(0)->setAmbient(Ogre::ColourValue(0.2, 0.2, 0.3, 1.0));
	this->tileMaterial->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(0.8, 0.8, 0.8, 1.0));
	this->tileMaterial->setColourWriteEnabled(true);

	this->tileSize = tileSize;
	this->meshName = "ground";
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		this->meshName, RGN_DEFAULT,
		plane,
		this->tileSize, this->tileSize, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);

	std::cout << "tilehandler singleton init\n";
}

void TileHandler::update(Real elapsedTime) {
	for (Ogre::SceneNode* tile : tiles) {
		//Update tile colour or something
	}
}

std::vector<SceneNode*> TileHandler::listTiles()
{
	return tiles;
}

void TileHandler::createTiles(float x0, float x1, float z0, float z1) {
	
	if (x0 > x1 || z0 > z1 || tileSize <= 0.0f) {
		std::cout << "attempted to create grid with invalid shape\n";
		return;
	}
	

	float z = z0;
	while (z < z1) {
		float x = x0;
		while (x <= x1) {
			createTile(
				SpaceClamper::getInstance()->clampX(x),
				SpaceClamper::getInstance()->clampZ(z),
				ColourValue::Red
			);
			x += tileSize;
		}
		z += tileSize;
	}
}