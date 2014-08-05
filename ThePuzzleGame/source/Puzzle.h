#define MAX_PARSED_INT_LENGTH 1
#define MAX_PARSED_MOVES_LENGTH 2
#define SEPARATOR_LENGTH 1
#define NUMBER_OF_ELEMENTS 4

class Puzzle
{
private:

	// The current puzzle field.
	int *field;

	// The initial puzzle field.
	int *fieldPrev;

	// The size of the current field.
	int size_X = 0, size_Y = 0;

	// The start position of the Puzzle
	int start_X = 0, start_Y = 0;

	// The available moves left.
	int moves = 0;

	// A String containing all the moves made to complete a puzzle.
	char *s;

	// The index of the next free position in *s.
	int cs = 0;

	// Appends a number to a string.
	void appendNumberToString(char *f, int n, const int max);

	// Reads a number from a string until it reaches a non-digit symbol, the end of the string or has read more symbols than max_length.
	int readNumber(char **f, int max_length);

	// Skips any number of non-digit symbols until it reaches a number, the end of the string or has skipped more than max_length symbols.
	void skipNonDigits(char **f, int max_length);

	// Reads a field information from a string with the size of the initialized array.
	void readField(char **f);

public:

	// Initialize a Puzzle from a string
	Puzzle(char *f);

	// Initialize an empty Puzzle, that has to be solved with the provided number of moves.
	Puzzle(int x, int y, int moves);

	// Destroy the created Puzzle
	~Puzzle();

	// Initialize field arrays based on field size.
	void initializeFieldArrays(int x, int y);

	// Load a field from a string. The string should be in the following format:
	// SIZE_X#SIZE_Y#START_X#START_Y#VALID_MOVES#FIELD
	void loadFromString(char* f);

	// Generate a random field using the provided random seed.
	void generateRandom(int seed);

	// Encode the current puzzle as a string.
	char* getAsString();

	// Return the X size of the field
	int getSizeX();

	// Return the Y size of the field
	int getSizeY();

	// Returns the index of element in position XxY
	int getIndex(int x, int y);

	// Print the field to the standard output as a matrix.
	void printAsMatrix();

	// Print the field to the standard output as a line.
	void printLine();

	// Checks if the Puzzle is solved.
	bool isSolved();

	// Checks if two puzzles are equal.
	bool isEqual(Puzzle* p);

	// Checks if there are changes to the current Puzzle, based on the previous field.
	bool hasChanges();

	// Returns the element at position XxY
	int getElement(int x, int y);

	// Removes the element at position XxY
	void removeElement(int x, int y);

	// Restores the element at position XxY to el.
	void restoreElement(int x, int y, int el);

	// Reverts all changes to the Puzzle.
	void revert();

	// Changes the field to the given array.
	void setField(int *f);

	// Removes all elements that are "visible" from position XxY and are from type el.
	void removeColor(int x, int y, int el, bool* visited);

	// Creates a copy of the current Puzzle.
	Puzzle* createCopy(int moves, int currentMove);

	// Generates all solutions to the current puzzle.
	void findAllSolutions(int* solutions);
};