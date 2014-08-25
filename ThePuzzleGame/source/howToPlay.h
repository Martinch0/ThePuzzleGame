#include "scene.h"

class HowToPlay : public Scene
{
protected:
	//UI Components
	CSprite* backButton;

public:
	HowToPlay();
	~HowToPlay();

	//Initialise the menu
	void Init();

	//Update the menu
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	//Render the menu
	void Render();
};