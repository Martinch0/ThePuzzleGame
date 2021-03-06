#include "s3e.h"
#include "IwDebug.h"
#include "Iw2D.h"
#include "input.h"
#include "scene.h"
#include "mainMenu.h"
#include "howToPlay.h"
#include "field.h"
#include "resources.h"

#define FRAMES_PER_SECOND 30.0f
#define FRAME_TIME (1.0f / FRAMES_PER_SECOND)
#define FRAME_TIME_MS (FRAME_TIME * 1000.0f)


// Main entry point for the application
int main()
{
    //Initialise graphics system(s)
	Iw2DInit();

	//Create resources
	g_pResources = new Resources();

	//Create scene manager
	g_pSceneManager = new SceneManager();

	// Set up input systems
	g_Input = new Input();

	//Init the main menu
	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	// Init the field
	Field* field = new Field();
	field->SetName("field");
	// Creates random puzzle
	Puzzle *p = new Puzzle(7, 7, 7);
	p->generateRandom(1);
	field->Init(p);
	g_pSceneManager->Add(field);

	//Init the howToPlay
	HowToPlay* howToPlay = new HowToPlay();
	howToPlay->SetName("howtoplay");
	howToPlay->Init();
	g_pSceneManager->Add(howToPlay);

	// Switch to the main menu
	g_pSceneManager->SwitchTo(main_menu);

	// Initialize variables for Frame Rate control
	uint64 frame_start_time = 0;
	int yield = 0;

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
		// Record start time of frame.
		frame_start_time = s3eTimerGetMs();

        //Update the input systems
		g_Input->Update();

		//Update scene manager
		g_pSceneManager->Update(FRAME_TIME);

		// Clear screen
		Iw2DSurfaceClear(0xff000000);

		//Render scene manager
		g_pSceneManager->Render();

		// Show the drawing surface
		Iw2DSurfaceShow();

        // Calculate time to sleep for having a fixed frame rate.
		yield = (int)(FRAME_TIME_MS - (s3eTimerGetMs() - frame_start_time));
		if (yield < 0)
			yield = 0;
		// Sleep to allow the OS to process events etc.
        s3eDeviceYield(yield);
    }

    //Terminate modules being used
	delete g_Input;
	delete g_pSceneManager;
	delete g_pResources;
	Iw2DTerminate();
    
    // Return
    return 0;
}
