#include "scene.h"
#include "Puzzle.h"
#include "input.h"
#include "resources.h"

class Field : public Scene
{
private:
	int field_size; // the size of the field array.
	CSprite **field; // array of Sprites to display on screen.
	Puzzle *p; // The current Puzzle assigned to the field.

	// Synchronizes the field in the Puzzle with the field of Sprites.
	void updateField(bool initial = false);
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