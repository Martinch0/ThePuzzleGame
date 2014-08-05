#include "Puzzle.h"
#include <stdlib.h>
#include <iostream>

void Puzzle::appendNumberToString(char *f, int n, const int max)
{
	char a[8];
	int i = 0;
	do
	{
		a[i] = (n % 10) + '0';
		i++;
		n /= 10;
	} while (i < max);
	while (i > 0)
	{
		f[max - i] = a[i-1];
		i--;
	}
}

int Puzzle::readNumber(char **f, int max_length)
{
	int r = 0;
	while (*f[0] >= '0' && *f[0] <= '9' && *f[0] != 0 && max_length > 0)
	{
		r *= 10;
		r += *f[0] - '0';
		(*f)++;
		max_length--;
	}
	return r;
}

void Puzzle::skipNonDigits(char **f, int max_length)
{
	while ((*f[0] < '0' || *f[0] > '9') && *f[0] != 0 && max_length > 0)
	{
		(*f)++;
		max_length--;
	}
}

void Puzzle::readField(char **f)
{
	int pos = 0;
	while (*f[0] >= '0' && *f[0] <= '9' && *f[0] != 0 && pos < this->size_X * this->size_Y)
	{
		this->field[pos] = this->fieldPrev[pos] = (*f)[0] - '0';
		(*f)++;
		pos++;
	}
}

Puzzle::Puzzle(char *f)
{
	loadFromString(f);
	this->s = new char[64];
}

Puzzle::Puzzle(int x, int y, int moves)
{
	initializeFieldArrays(x, y);
	this->moves = moves;
	this->s = new char[64];
}

Puzzle::~Puzzle()
{
	if (this->size_X != 0 || this->size_Y)
	{
		delete[] field;
		delete[] fieldPrev;
	}
	delete[] s;
}

void Puzzle::initializeFieldArrays(int x, int y)
{
	int sq = x * y;
	int size = 2;
	while (size < sq)
		size *= 2;
	if (this->size_X != 0 || this->size_Y != 0)
	{
		delete[] field;
		delete[] fieldPrev;
	}
	this->field = new int[size];
	this->fieldPrev = new int[size];
	this->size_X = x;
	this->size_Y = y;
}

void Puzzle::loadFromString(char *f)
{
	// read the x size of the field
	int x = readNumber(&f, MAX_PARSED_INT_LENGTH);
	skipNonDigits(&f, SEPARATOR_LENGTH);

	// read the y size of the field
	int y = readNumber(&f, MAX_PARSED_INT_LENGTH);
	skipNonDigits(&f, SEPARATOR_LENGTH);

	// read the start x of the field
	this->start_X = readNumber(&f, MAX_PARSED_INT_LENGTH);
	skipNonDigits(&f, SEPARATOR_LENGTH);

	// read the start y of the field
	this->start_Y = readNumber(&f, MAX_PARSED_INT_LENGTH);
	skipNonDigits(&f, SEPARATOR_LENGTH);

	this->moves = readNumber(&f, MAX_PARSED_MOVES_LENGTH);
	skipNonDigits(&f, SEPARATOR_LENGTH);

	// initialize field arrays and load them from the string
	initializeFieldArrays(x, y);
	readField(&f);
}

void Puzzle::generateRandom(int seed)
{
	// generate a random field.
	srand(seed);
	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			this->field[this->getIndex(x, y)] = this->fieldPrev[this->getIndex(x, y)] = rand() % NUMBER_OF_ELEMENTS + 1;
		}
	}

	// set the start X and Y to the middle of the field.
	this->start_X = this->size_X / 2;
	this->start_Y = this->size_Y / 2;
	field[this->getIndex(this->start_X, this->start_Y)] = 0;
}

char* Puzzle::getAsString()
{
	char *r = new char[1 + MAX_PARSED_INT_LENGTH * 4 + 4 + MAX_PARSED_MOVES_LENGTH + 1 + this->size_X * this->size_Y];
	int i = 0;

	appendNumberToString(&r[i], this->size_X, MAX_PARSED_INT_LENGTH);
	i += MAX_PARSED_INT_LENGTH;
	r[i++] = '#';

	appendNumberToString(&r[i], this->size_Y, MAX_PARSED_INT_LENGTH);
	i += MAX_PARSED_INT_LENGTH;
	r[i++] = '#';

	appendNumberToString(&r[i], this->start_X, MAX_PARSED_INT_LENGTH);
	i += MAX_PARSED_INT_LENGTH;
	r[i++] = '#';

	appendNumberToString(&r[i], this->start_Y, MAX_PARSED_INT_LENGTH);
	i += MAX_PARSED_INT_LENGTH;
	r[i++] = '#';

	appendNumberToString(&r[i], this->moves, MAX_PARSED_MOVES_LENGTH);
	i += MAX_PARSED_MOVES_LENGTH;
	r[i++] = '#';

	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			r[i++] = this->field[this->getIndex(x, y)] + '0';
		}
	}

	r[i] = 0;

	return r;
}

int Puzzle::getSizeX()
{
	return this->size_X;
}

int Puzzle::getSizeY()
{
	return this->size_Y;
}

int Puzzle::getIndex(int x, int y)
{
	return y * this->size_X + x;
}

void Puzzle::printAsMatrix()
{
	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			std::cout << this->field[this->getIndex(x, y)] << ' ';
		}
		std::cout << std::endl;
	}
}

void Puzzle::printLine()
{
	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			std::cout << this->field[this->getIndex(x, y)];
		}
	}
}

bool Puzzle::isSolved()
{
	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			if (this->field[this->getIndex(x, y)] != 0)
				return false;
		}
	}
	return true;
}

bool Puzzle::isEqual(Puzzle* p)
{
	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			if (this->field[this->getIndex(x, y)] != p->field[this->getIndex(x, y)])
				return false;
		}
	}
	return true;
}

bool Puzzle::hasChanges()
{
	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			if (this->field[this->getIndex(x, y)] != this->fieldPrev[this->getIndex(x, y)])
				return true;
		}
	}
	return false;
}

int Puzzle::getElement(int x, int y)
{
	return this->field[this->getIndex(x, y)];
}

void Puzzle::removeElement(int x, int y)
{
	this->field[this->getIndex(x, y)] = 0;
}

void Puzzle::restoreElement(int x, int y, int el)
{
	this->field[this->getIndex(x, y)] = el;
}

void Puzzle::revert()
{
	for (int y = 0; y < this->size_Y; y++)
	{
		for (int x = 0; x < this->size_X; x++)
		{
			this->field[this->getIndex(x, y)] = this->fieldPrev[this->getIndex(x, y)];
		}
	}
}

void Puzzle::setField(int *f)
{
	this->field = f;
}

void Puzzle::removeColor(int x, int y, int el, bool* visited)
{
	if (this->isSolved())
	{
		return;
	}
	visited[this->getIndex(x, y)] = true;
	if (this->getElement(x, y) == el)
	{
		this->removeElement(x,y);
		if (x + 1 < this->size_X && !visited[this->getIndex(x + 1,y)]) removeColor(x + 1, y, el, visited);
		if (x - 1 >= 0 && !visited[this->getIndex(x - 1, y)]) removeColor(x - 1, y, el, visited);
		if (y + 1 < this->size_Y && !visited[this->getIndex(x, y + 1)]) removeColor(x, y + 1, el, visited);
		if (y - 1 >= 0 && !visited[this->getIndex(x, y - 1)]) removeColor(x, y - 1, el, visited);
	}
	else if (this->getElement(x,y) == 0)
	{
		if (x + 1 < 7 && !visited[this->getIndex(x + 1, y)]) removeColor(x + 1, y, el, visited);
		if (x - 1 >= 0 && !visited[this->getIndex(x - 1, y)]) removeColor(x - 1, y, el, visited);
		if (y + 1 < 7 && !visited[this->getIndex(x, y + 1)]) removeColor(x, y + 1, el, visited);
		if (y - 1 >= 0 && !visited[this->getIndex(x, y - 1)]) removeColor(x, y - 1, el, visited);
	}
}

Puzzle* Puzzle::createCopy(int moves, int currentMove)
{
	Puzzle *p = new Puzzle(this->size_X, this->size_Y, moves);
	for (int i = 0; i < 64; i++)
	{
		p->field[i] = p->fieldPrev[i] = this->field[i];
		p->s[i] = this->s[i];
	}
	p->s[cs] = currentMove + '0';
	p->cs = cs + 1;
	return p;
}

void Puzzle::findAllSolutions(int* solutions)
{
	if (this->isSolved())
	{
		return;
	}

	Puzzle *p = NULL;
	
	for (int i = 1; i <= NUMBER_OF_ELEMENTS; i++)
	{
		bool v[64] = { false };
		this->removeColor(this->start_X, this->start_Y, i, v);
		if (this->isSolved())
		{
			solutions[moves]++;
			this->s[this->cs] = ('0' + i);
			this->s[this->cs + 1] = 0;
			std::cout << this->s << std::endl;
		}
		if (this->hasChanges())
		{
			p = this->createCopy(moves + 1, i);
			p->findAllSolutions(solutions);
			delete p;
		}
		this->revert();
	}
}