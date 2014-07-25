class Puzzle {
private:
	int *field;
	int *fieldPrev;
	int moves = 0;
	char *s;
	int cs = 0;
public:
	Puzzle(int moves) {
		this->field = new int[64];
		this->fieldPrev = new int[64];
		this->moves = moves;
		s = new char[64];
	}

	~Puzzle() {

	}

	void generate(int seed);
	void printAsMatrix();
	void printLine();
	bool isSolved();
	bool isEqual(Puzzle* p);
	bool hasChanges();
	int getElement(int i, int j);
	void removeElement(int i, int j);
	void restoreElement(int i, int j, int el);
	void revert();
	void setField(int *f);
	void removeColor(int i, int j, int el, bool* visited);
	Puzzle* createCopy(int moves, int currentMove);
	void findAllSolutions(int* solutions);
};