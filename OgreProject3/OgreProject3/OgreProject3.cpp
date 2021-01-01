// OgreProject3.cpp : Defines the entry point for the application.
//

#include "OgreProject3.h"
#include "App.h"

using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        App app;
        app.initApp();


		auto m_pRenderWnd = app.getRenderWindow();

		size_t hWnd = 0;
		OIS::ParamList paramList;
		m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);

		paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

		auto InputManager = OIS::InputManager::createInputSystem(paramList);

		auto keyboard = static_cast<OIS::Keyboard*>(InputManager->createInputObject(OIS::OISKeyboard, true));
		auto mouse = static_cast<OIS::Mouse*>(InputManager->createInputObject(OIS::OISMouse, true));

		auto window = app.getRenderWindow();
		auto timer = new Ogre::Timer();

		while (!window->isClosed())
		{
			Ogre::Real deltaTime = timer->getMilliseconds()/1000.0F;
			timer->reset();

			// Drawings
			window->update();
			window->update(false);

			// The drawn surface is then shown on the screen
			// (google "double buffering" if you want more details).
			// I always use vertical synchro.
			window->swapBuffers();

			// This update some internal counters and listeners.
			// Each render surface (window/rtt/mrt) that is 'auto-updated' has got its 'update' function called.
			app.getRoot()->renderOneFrame();
			keyboard->capture();
			mouse->capture();
			app.update(deltaTime, keyboard, mouse);
		}
        app.closeApp();

    }
    catch (Ogre::Exception& e)
    {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }
    
	cout << "Bye!" << endl;
	return 0;
}
