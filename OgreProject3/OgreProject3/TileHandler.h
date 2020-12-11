#pragma once
#include <vector>
#include <Ogre.h>
#include <iostream>

using namespace Ogre;

class TileHandler
{
private:
	std::vector<Ogre::SceneNode*> tiles;
	SceneManager* sceneMgr;
	Ogre::MaterialPtr tileMaterial;
	TileHandler() {};
public:
	static TileHandler* getInstance() {
		static TileHandler instance;
		return &instance;
	}
	void init(SceneManager* sceneMgr);
	void update(Real elapsedTime);
public:
	void createTiles(float x0, float x1, float z0, float z1, float a);
	Ogre::SceneNode* createTile(float x, float z, float a, Ogre::ColourValue c);
	std::vector<SceneNode*> listTiles();
};

inline Ogre::SceneNode* TileHandler::createTile(float x, float z, float a, Ogre::ColourValue c)
{
	float half = a * 0.5f;

	std::ostringstream name1;
	name1 << "triangle" << x << " " << z << "1";
	std::ostringstream name2;
	name2 << "triangle" << x << " " << z << "2";

	Ogre::ManualObject* triangle1 = sceneMgr->createManualObject(name1.str().c_str());
	triangle1->begin(tileMaterial);
	triangle1->position(half, 0, -half);
	triangle1->colour(c);
	triangle1->position(-half, 0, -half);
	triangle1->colour(c);
	triangle1->position(-half, 0, half);
	triangle1->colour(c);
	triangle1->end();

	Ogre::ManualObject* triangle2 = sceneMgr->createManualObject(name2.str().c_str());
	
	triangle2->begin(tileMaterial);
	triangle2->position(half, 0, -half);
	triangle2->colour(c);
	triangle2->position(-half, 0, half);
	triangle2->colour(c);
	triangle2->position(half, 0, half);
	triangle2->colour(c);
	triangle2->end();

	Ogre::SceneNode* square = sceneMgr->getRootSceneNode()->createChildSceneNode();
	square->attachObject(triangle1);
	square->attachObject(triangle2);
	square->setPosition(x, 0, z);

	return square;
}