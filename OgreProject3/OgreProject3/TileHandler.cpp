#include "TileHandler.h"
#include "SpaceClamper.h"
#include <iostream>

void TileHandler::init(SceneManager* sceneMgr, float tileSize) {
	this->sceneMgr = sceneMgr;
	this->tiles = std::vector<Ogre::SceneNode*>();
	this->gen = std::mt19937(rd());
	this->threeDis = std::uniform_int_distribution<>(0, 2);

	auto textureManager = TextureManager::getSingletonPtr();

	auto textureName = "road.png";
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


	this->tileMaterial = Ogre::MaterialManager::getSingleton().create("tile material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
	this->tileMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(textureName);
	this->tileMaterial->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(0.8, 0.8, 0.8, 1.0));
	this->tileMaterial->setColourWriteEnabled(true);
	this->tileMaterial->setReceiveShadows(true);

	this->tileSize = tileSize;
	this->meshName = "ground";
	Plane plane(Vector3::UNIT_Y, 0);
	auto tile = MeshManager::getSingleton().createPlane(
		this->meshName, RGN_DEFAULT,
		plane,
		this->tileSize, this->tileSize, 20, 20,
		true,
		1, 1, 1,
		Vector3::UNIT_Z);

	tile->prepareForShadowVolume();
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

	ResourceGroupManager& resMng = ResourceGroupManager::getSingleton();
	auto textureName = "environmentColors.png";
	float m_x = SpaceClamper::getInstance()->clampX((x0 + x1) / 2);

	// University
	for (int i = -1; i <= 1; i++) {
		if (i == 0) {
			const char* uniMeshName = "University";
			std::string uBuf(uniMeshName);
			uBuf.append(".mesh");
			Entity* uniEntity = sceneMgr->createEntity("u" + std::to_string(i), uBuf);
			uniEntity->setCastShadows(false);
			Ogre::SceneNode* university = sceneMgr->getRootSceneNode()->createChildSceneNode();
			university->rotate(Vector3::UNIT_Y, Degree(180));
			university->attachObject(uniEntity);
			university->setPosition(
				m_x + Ogre::Real(i) * uniEntity->getBoundingBox().getSize().x,
				0.0,
				z0 - uniEntity->getBoundingBox().getHalfSize().z - Ogre::Real(2.5)
			);
		}
		else {
			const char* antiMeshName = "Grass_Lane";
			std::string aBuf(antiMeshName);
			aBuf.append(".mesh");
			Entity* antiEntity = sceneMgr->createEntity("u" + std::to_string(i), aBuf);
			antiEntity->setCastShadows(false);
			Ogre::SceneNode* antiversity = sceneMgr->getRootSceneNode()->createChildSceneNode();
			antiversity->rotate(Vector3::UNIT_Y, Degree(180));
			antiversity->attachObject(antiEntity);
			antiversity->setPosition(
				m_x + Ogre::Real(i) * antiEntity->getBoundingBox().getSize().x,
				0.0,
				z0 - antiEntity->getBoundingBox().getHalfSize().z - Ogre::Real(2.5)
			);
		}
	}

	// Antiversity
	for (int i = -1; i <= 1; i++) {
		const char* antiMeshName = "Grass_Lane";
		std::string aBuf(antiMeshName);
		aBuf.append(".mesh");
		Entity* antiEntity = sceneMgr->createEntity("a" + std::to_string(i), aBuf);
		antiEntity->setCastShadows(false);
		Ogre::SceneNode* antiversity = sceneMgr->getRootSceneNode()->createChildSceneNode();
		antiversity->rotate(Vector3::UNIT_Y, Degree(180));
		antiversity->attachObject(antiEntity);
		antiversity->setPosition(
			m_x + Ogre::Real(i) * antiEntity->getBoundingBox().getSize().x,
			0.0,
			z1 + tileSize
		);
	}
}

void TileHandler::createPauseLane(float x0, float x1, float z) {
	// LOAD TERRAIN MODEL
	ResourceGroupManager& resMng = ResourceGroupManager::getSingleton();

	const char* meshName;
	int v = threeDis(gen);
	switch (v) {
	case 0: meshName = "Grass_Lane"; break;
	case 1: meshName = "2_Tree_Lane"; break;
	case 2: meshName = "3_Tree_Lane"; break;
	default: meshName = "Grass_Lane"; break;
	}
	auto textureName = "environmentColors.png";
	std::string buf(meshName);
	buf.append(".mesh");

	float x = x0;
	float x_end = x1;
	bool first = true;
	while (x < x_end) {
		Entity* envEntity = sceneMgr->createEntity("PauseLane_" + std::to_string(z) + "_" + std::to_string(x), buf);
		envEntity->setCastShadows(false);
		Ogre::Real ratio = tileSize / envEntity->getBoundingBox().getSize().z;

		Ogre::SceneNode* lane = sceneMgr->getRootSceneNode()->createChildSceneNode();

		lane->rotate(Vector3::UNIT_Y, Degree(180));
		lane->attachObject(envEntity);
		if (first) {
			x -= envEntity->getBoundingBox().getHalfSize().x * ratio;
			x_end += envEntity->getBoundingBox().getHalfSize().x * ratio;
			first = false;
		}
		lane->setPosition(
			SpaceClamper::getInstance()->clampX(x),
			0.0,
			SpaceClamper::getInstance()->clampZ(z)
		);
		x += envEntity->getBoundingBox().getSize().x * ratio;
		lane->setScale(ratio, ratio, ratio);
	}
}

void TileHandler::createRoadLanes(float x0, float x1, float z0, float z1) {
	ResourceGroupManager& resMng = ResourceGroupManager::getSingleton();

	const char* meshName;
	meshName = "Road_Lane";
	auto textureName = "environmentColors.png";
	std::string buf(meshName);
	buf.append(".mesh");


	float x = x0;
	float x_end = x1;
	float z = (SpaceClamper::getInstance()->clampZ(z0) + SpaceClamper::getInstance()->clampZ(z1)) / 2.0;
	bool first = true;
	while (x < x_end) {
		Entity* envEntity = sceneMgr->createEntity("RoadLane_" + std::to_string(z) + "_" + std::to_string(x), buf);
		envEntity->setCastShadows(false);
		Ogre::Real ratio = (2 * tileSize) / envEntity->getBoundingBox().getSize().z;

		Ogre::SceneNode* lane = sceneMgr->getRootSceneNode()->createChildSceneNode();

		lane->rotate(Vector3::UNIT_Y, Degree(180));
		lane->attachObject(envEntity);
		if (first) {
			x -= envEntity->getBoundingBox().getHalfSize().x * ratio;
			x_end += envEntity->getBoundingBox().getHalfSize().x * ratio;
			first = false;
		}
		lane->setPosition(
			SpaceClamper::getInstance()->clampX(x),
			0.0,
			z
		);
		x += envEntity->getBoundingBox().getSize().x * ratio;
		
		lane->setScale(ratio, ratio, ratio);
	}
}
