#pragma once
#include <vector>
#include <Ogre.h>

using namespace Ogre;

class TileHandler
{
private:
	std::vector<Ogre::SceneNode*> tiles;
	SceneManager* sceneMgr;
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

	Ogre::ManualObject* triangle1 = sceneMgr->createManualObject("Triangle1");
	triangle1->begin("BaseWhiteNoLighting");
	triangle1->position(half, 0, -half);
	triangle1->colour(c);
	triangle1->position(-half, 0, -half);
	triangle1->colour(c);
	triangle1->position(-half, 0, half);
	triangle1->colour(c);
	triangle1->end();

	Ogre::ManualObject* triangle2 = sceneMgr->createManualObject("Triangle2");
	triangle2->begin("BaseWhiteNoLighting");
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