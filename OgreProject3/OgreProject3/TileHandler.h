#pragma once
#include <vector>
#include <Ogre.h>
#include <iostream>
#include <random>

using namespace Ogre;

class TileHandler
{
private:
	float tileSize;
	std::string meshName;
	std::vector<Ogre::SceneNode*> tiles;
	SceneManager* sceneMgr;
	Ogre::MaterialPtr tileMaterial;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> twoDis;
	TileHandler() {};
public:
	static TileHandler* getInstance() {
		static TileHandler instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr, float tileSize);
	void update(Real elapsedTime);
public:
	void createTiles(float x0, float x1, float z0, float z1);
	void createPauseLane(float leftBound, float rightBound, float z);
	void createRoadLanes(float x0, float x1, float z0, float z1);
	Ogre::SceneNode* createTile(float x, float z, Ogre::ColourValue c);
	std::vector<SceneNode*> listTiles();
};

inline Ogre::SceneNode* TileHandler::createTile(float x, float z, Ogre::ColourValue c)
{
	Entity* groundEntity = sceneMgr->createEntity(meshName);
	groundEntity->setMaterial(this->tileMaterial);
	groundEntity->setCastShadows(true);
	Ogre::SceneNode* square = sceneMgr->getRootSceneNode()->createChildSceneNode();
	//square->attachObject(groundEntity);
	//square->setPosition(x, 0, z);
	
	return square;
}