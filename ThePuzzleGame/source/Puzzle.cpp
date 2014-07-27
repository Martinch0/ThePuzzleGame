#include "Puzzle.h"
#include <stdlib.h>
#include <iostream>

Puzzle::Puzzle(int moves)
{
	this->field = new int[64];
	this->fieldPrev = new int[64];
	this->moves = moves;
	s = new char[64];
}

Puzzle::~Puzzle()
{
	delete[] field;
	delete[] fieldPrev;
	delete[] s;
}

void Puzzle::generate(int seed)
{
	srand(seed);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			this->field[i * 7 + j] = this->fieldPrev[i * 7 + j] = rand() % 4 + 1;
		}
	}
	field[24] = 0;
}

void Puzzle::printLine()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			std::cout << this->field[i * 7 + j];
		}
	}
}

void Puzzle::printAsMatrix()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			std::cout << this->field[i * 7 + j] << ' ';
		}
		std::cout << std::endl;
	}
}

bool Puzzle::isSolved()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (this->field[i * 7 + j] != 0)
				return false;
		}
	}
	return true;
}

bool Puzzle::isEqual(Puzzle* p)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (this->field[i * 7 + j] != p->field[i * 7 + j])
				return false;
		}
	}
	return true;
}

bool Puzzle::hasChanges()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (this->field[i * 7 + j] != this->fieldPrev[i * 7 + j])
				return true;
		}
	}
	return false;
}

int Puzzle::getElement(int i, int j)
{
	return this->field[i * 7 + j];
}

void Puzzle::removeElement(int i, int j)
{
	this->field[i * 7 + j] = 0;
}

void Puzzle::restoreElement(int i, int j, int el)
{
	this->field[i * 7 + j] = el;
}

void Puzzle::revert()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			this->field[i * 7 + j] = this->fieldPrev[i * 7 + j];
		}
	}
}

void Puzzle::setField(int *f)
{
	this->field = f;
}

void Puzzle::removeColor(int i, int j, int el, bool* visited)
{
	if (this->isSolved())
	{
		return;
	}
	visited[i*7+j] = true;
	if (this->getElement(i, j) == el)
	{
		this->removeElement(i, j);
		if (i + 1 < 7 && !visited[(i + 1) * 7 + j]) removeColor(i + 1, j, el, visited);
		if (i - 1 >= 0 && !visited[(i - 1) * 7 + j]) removeColor(i - 1, j, el, visited);
		if (j + 1 < 7 && !visited[i * 7 + j + 1]) removeColor(i, j + 1, el, visited);
		if (j - 1 >= 0 && !visited[i * 7 + j - 1]) removeColor(i, j - 1, el, visited);
	}
	else if (this->getElement(i, j) == 0)
	{
		if (i + 1 < 7 && !visited[(i + 1) * 7 + j]) removeColor(i + 1, j, el, visited);
		if (i - 1 >= 0 && !visited[(i - 1) * 7 + j]) removeColor(i - 1, j, el, visited);
		if (j + 1 < 7 && !visited[i * 7 + j + 1]) removeColor(i, j + 1, el, visited);
		if (j - 1 >= 0 && !visited[i * 7 + j - 1]) removeColor(i, j - 1, el, visited);
	}
}

Puzzle* Puzzle::createCopy(int moves, int currentMove)
{
	Puzzle *p = new Puzzle(moves);
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
	bool v1[64] = { false };
	bool v2[64] = { false };
	bool v3[64] = { false };
	bool v4[64] = { false };
	Puzzle *p;
	this->removeColor(3, 3, 1, v1);
	if (this->isSolved())
	{
		solutions[moves]++;
		this->s[this->cs] = '1';
		std::cout << this->s << std::endl;
	}
	if (this->hasChanges())
	{
		p = this->createCopy(moves + 1, 1);
		p->findAllSolutions(solutions);
	}
	this->revert();
	this->removeColor(3, 3, 2, v2);
	if (this->isSolved())
	{
		solutions[moves]++;
		this->s[this->cs] = '2';
		std::cout << this->s << std::endl;
	}
	if (this->hasChanges())
	{
		p = this->createCopy(moves + 1, 2);
		p->findAllSolutions(solutions);
	}
	this->revert();
	this->removeColor(3, 3, 3, v3);
	if (this->isSolved())
	{
		solutions[moves]++;
		this->s[this->cs] = '3';
		std::cout << this->s << std::endl;
	}
	if (this->hasChanges())
	{
		p = this->createCopy(moves + 1, 3);
		p->findAllSolutions(solutions);
	}
	this->revert();
	this->removeColor(3, 3, 4, v4);
	if (this->isSolved())
	{
		solutions[moves]++;
		this->s[this->cs] = '4';
		std::cout << this->s << std::endl;
	}
	if (this->hasChanges())
	{
		p = this->createCopy(moves + 1, 4);
		p->findAllSolutions(solutions);
	}
}