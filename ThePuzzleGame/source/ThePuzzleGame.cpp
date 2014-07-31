#include "s3e.h"
#include "IwDebug.h"
#include "Iw2D.h"
#include "input.h"
#include "scene.h"
#include "mainMenu.h"


// Main entry point for the application
int main()
{
    //Initialise graphics system(s)
	Iw2DInit();

	//Create scene manager
	g_pSceneManager = new SceneManager();

	// Set up input systems
	g_Input = new Input();

	//Init the main menu
	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	//Init the game

	//Switch to the main menu
	g_pSceneManager->SwitchTo(main_menu);


    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {

        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

		//Update scene manager
		g_pSceneManager->Update(0.003f); //NEED FRAME LIMIT

		// Clear screen
		Iw2DSurfaceClear(0xff000000);

		//Render scene manager
		g_pSceneManager->Render();

		// Show the drawing surface
		Iw2DSurfaceShow();

        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    //Terminate modules being used
	delete g_Input;
	delete g_pSceneManager;
	Iw2DTerminate();
    
    // Return
    return 0;
}
