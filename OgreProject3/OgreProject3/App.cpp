#include "App.h"
Ogre::SceneNode* triangleNode;

bool move_left, move_right, move_forw, move_backw, move_up, move_down;

void App::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // set inital variable values
    move_left = move_right = move_forw = move_backw = move_up = move_down = false;

    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();
	
	// add resource folder to resourcegroupmanager
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources", "FileSystem");

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
    Ogre::Entity* ent = scnMgr->createEntity("Cube.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    node->setDirection(0.0F, 0.0F, M_PI);
    node->setPosition(0, 5, 2);


    scnMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

    /*Ogre::Light* light = scnMgr->createLight("MainLight");
    light->setPosition(20, 80, 50);*/
}

bool App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    std::cout << "Captured keypress" << 'n';
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        std::cout << "Pressed escape" << '\n';
        getRoot()->queueEndRendering();
    }

    return true;
}

bool App::textInput(const OgreBites::TextInputEvent& evt)
{
    std::cout << "Captured text input" << 'n';
    char c = *evt.chars;
    if (c == 'q') {
        move_up = true;
    }
    else if (c == 'w') {
        move_forw = true;
    }
    else if (c == 'e') {
        move_down = true;
    }
    else if (c == 'a') {
        move_left = true;
    }
    else if (c == 's') {
        move_backw = true;
    }
    else if (c == 'd') {
        move_right = true;
    }

    return true;
}

bool App::frameEnded(const Ogre::FrameEvent& evt)
{
    float unit = 0.1f;
    float x = 0, y = 0, z = 0;
    if (move_up) { y += unit; }
    if (move_forw) { z -= unit; }
    if (move_down) { y -= unit; }
    if (move_left) { x -= unit; }
    if (move_backw) { z += unit; }
    if (move_right) { x += unit; }
    move_left = move_right = move_forw = move_backw = move_up = move_down = false;

    triangleNode->translate(x, y, z);

    return true;
}
