#include "s3e.h"
#include "IwDebug.h"
#include "Iw2D.h"


// Main entry point for the application
int main()
{
    //Initialise graphics system(s)
	Iw2DInit();

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {

        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

		// Clear screen
		Iw2DSurfaceClear(0xff000000);
		// Show the drawing surface
		Iw2DSurfaceShow();

        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(10);
    }

    //Terminate modules being used
	Iw2DTerminate();
    
    // Return
    return 0;
}
