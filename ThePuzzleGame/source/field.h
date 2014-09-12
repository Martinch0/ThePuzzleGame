#include "scene.h"
#include "Puzzle.h"
#include "input.h"
#include "resources.h"
#include <vector>
#include <memory>

#define BUTTONS_NUMBER 4
#define FIELD_TOP_PADDING 150
#define BUTTONS_TOP_PADDING 750
#define STATE_PLAYING 1
#define STATE_PAUSED 2
#define STATE_LOST 3
#define STATE_WON 4

class Field : public Scene
{
private:
	int state; // the state of the current game.
	int field_size; // the size of the field array.
	CSprite **field; // array of Sprites to display the field on screen.
	CSprite **buttons; // array of Sprites to display the buttons on screen
	CSprite *pauseButton;
	CSprite *restartButton;
	CLabel *turnsLeft;
	CLabel *gameOver;
	Puzzle *p; // The current Puzzle assigned to the field.

	// Synchronizes the field in the Puzzle with the field of Sprites.
	void updateField(bool initial = false);

	// Deletes all elements related to the field
	void deleteField();

	// Creates the buttons
	void updateButtons(bool initial = false);

	// Deletes all elements related to the buttons
	void deleteButtons();

	// Creates and updates the score label
	void updateScore(bool initial = false);

	// Updates the game state
	void updateGameState();

	// Handles all input for the current scene.
	void checkForInput();

	// Reset the field
	void reset();
public:
	Field();
	~Field();

	// Initializes a field connected to the specified Puzzle.
	void Init(Puzzle *p);

	// Deletes the current Puzzle attached to the scene.
	void Exit();

	// Updates each frame.
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render.
	void Render();
};