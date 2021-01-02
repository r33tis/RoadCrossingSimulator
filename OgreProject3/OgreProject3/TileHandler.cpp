#include "TileHandler.h"
#include "SpaceClamper.h"
#include <iostream>

void TileHandler::init(SceneManager* sceneMgr, float tileSize) {
	this->sceneMgr = sceneMgr;
	this->tiles = std::vector<Ogre::SceneNode*>();

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
	



	// LOAD TERRAIN MODEL
	ResourceGroupManager& resMng = ResourceGroupManager::getSingleton();


	/*MaterialManager& lMaterialManager = MaterialManager::getSingleton();

	Image envImage;
	envImage.load(textureName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	TexturePtr envTexture;
	envTexture = textureManager->createManual(
		textureName,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		envImage.getWidth(), envImage.getHeight(),
		0, PF_X8R8G8B8);
	envTexture->loadImage(envImage);


	MaterialPtr lMaterial = lMaterialManager.create(mewshName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	lMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(textureName);
	lMaterial->setReceiveShadows(false);*/
	
	const char* meshName = "Environment";
	textureName = "environmentColors.png";

	//Ogre::MaterialManager::getSingleton().load("environmentColors", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//auto material = Ogre::MaterialManager::getSingleton().getByName("environmentColors");
	//material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("environmentColors.png");
	//material->load();

	std::string buf(meshName);
	buf.append(".mesh");

	

	auto envEntity = sceneMgr->createEntity("Environment", buf);
	envEntity->setCastShadows(false);

	Ogre::SceneNode* square = sceneMgr->getRootSceneNode()->createChildSceneNode();

	square->attachObject(envEntity);
	square->rotate(Vector3::UNIT_Y, Degree(180));
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