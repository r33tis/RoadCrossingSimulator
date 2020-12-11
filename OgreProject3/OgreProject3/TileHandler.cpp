#include "TileHandler.h"
#include <iostream>

void TileHandler::init(SceneManager* sceneMgr) {
	this->sceneMgr = sceneMgr;
	this->tiles = std::vector<Ogre::SceneNode*>();
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

void TileHandler::createTiles(float x0, float x1, float z0, float z1, float a) {
	
	if (x0 > x1 || z0 > z1 || a <= 0.0f) {
		std::cout << "attempted to create grid with invalid shape\n";
		return;
	}

	float z = z0;
	while (z < z1) {
		float x = x0;
		while (x < x1) {
			createTile(x, z, 1.0, ColourValue::Red);
			x += a;
		}
		z += a;
	}
}