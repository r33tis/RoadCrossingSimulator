// OgreProject3.cpp : Defines the entry point for the application.
//

#include "OgreProject3.h"
#include "App.h"

using namespace std;

int main(int argc, char* argv[])
{

    cout << "Hello." << endl;
    try
    {
    

        App app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();

    }
    catch (Ogre::Exception& e)
    {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }
    
	cout << "Hello CMake." << endl;
	return 0;
}
