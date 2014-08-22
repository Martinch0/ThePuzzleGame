#include "field.h"
#include <iostream>

void Field::updateField(bool initial)
{
	int element_size = g_pResources->getElement(p->getElement(0, 0))->GetWidth();
	int field_padding = element_size / 5;

	float scale = IwGxGetScreenWidth() / ORIG_WIDTH;

	int max_x = p->getSizeX();
	int max_y = p->getSizeY();

	int left_padding = (ORIG_WIDTH - (max_x * element_size + field_padding * (max_x - 1)))/2;
	int top_padding = 50;
	for (int y = 0; y < max_y; y++)
	{
		for (int x = 0; x < max_x; x++)
		{
			CSprite *tmp;
			if (initial)
			{
				tmp = new CSprite();
				tmp->SetImage(g_pResources->getElement(p->getElement(x, y)));
				this->field[p->getIndex(x, y)] = tmp;
				AddChild(tmp);
			}
			else
			{
				tmp = this->field[p->getIndex(x, y)];
			}
			tmp->m_X = (left_padding + x * (tmp->GetImage()->GetWidth() + field_padding)) * scale;
			tmp->m_Y = (top_padding + y * (tmp->GetImage()->GetHeight() + field_padding)) * scale;
			tmp->m_W = tmp->GetImage()->GetWidth() * scale;
			tmp->m_H = tmp->GetImage()->GetHeight() * scale;
			tmp->m_ScaleX = scale;
			tmp->m_ScaleY = scale;
		}
	}
}

Field::Field()
{
}

Field::~Field()
{
	this->Exit();
}

void Field::Init(Puzzle *p)
{
	Scene::Init();

	// Save the pointer to the Puzzle
	this->p = p;

	// Initialize the field array
	int square = p->getSizeX() * p->getSizeY();
	this->field_size = 2;
	while (this->field_size < square)
	{
		this->field_size *= 2;
	}
	this->field = new CSprite*[this->field_size];

	// Do a first update on the field.
	this->updateField(true);
}

void Field::Exit()
{
	if (this->field_size != 0)
	{
		this->field_size = 0;
		delete p;
		delete field;
	}
}

void Field::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
	{
		return;
	}

	updateField(false);

	Scene::Update(deltaTime, alphaMul);
}

void Field::Render()
{
	Scene::Render();
}