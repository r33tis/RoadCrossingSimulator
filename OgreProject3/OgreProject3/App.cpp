#include "App.h"


void App::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // finally something to render
    /*Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);*/

    Ogre::ManualObject* triangle = scnMgr->createManualObject("Triangle");

    // ~ glBegin, glVertex, glEnd
    // "BaseWhiteNoLighting" is a built-in name for a basic non-lit material
    triangle->begin("BaseWhiteNoLighting");
    triangle->position(0, 0.5, 0);            // ~ glVertex.
                                              // Contrary to OpenGL we *first* must create the vertex
    triangle->colour(Ogre::ColourValue::Red); // .. and then provide its attributes such as color (~ glColor)
    triangle->position(-0.5, -0.5, 0);
    triangle->colour(Ogre::ColourValue::Green);
    triangle->position(0.5, -0.5, 0);
    triangle->colour(Ogre::ColourValue::Blue);
    triangle->end();


    Ogre::SceneNode* triangleNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    triangleNode->attachObject(triangle);


    scnMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

    /*Ogre::Light* light = scnMgr->createLight("MainLight");
    light->setPosition(20, 80, 50);*/
}
