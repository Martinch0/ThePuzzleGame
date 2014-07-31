#include "scene.h"

class MainMenu : public Scene
{
protected:
	//UI Components
	CSprite* playButton;

public:
	MainMenu();
	~MainMenu();

	//Initialise the menu
	void Init();

	//Update the menu
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	//Render the menu
	void Render();
};