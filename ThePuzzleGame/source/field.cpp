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
				this->field[p->getIndex(x, y)] = new CSprite();
				AddChild(this->field[p->getIndex(x, y)]);
			}
			tmp = this->field[p->getIndex(x, y)];
			tmp->SetImage(g_pResources->getElement(p->getElement(x, y)));
			tmp->m_X = (left_padding + x * (tmp->GetImage()->GetWidth() + field_padding)) * scale;
			tmp->m_Y = (top_padding + y * (tmp->GetImage()->GetHeight() + field_padding)) * scale;
			tmp->m_W = tmp->GetImage()->GetWidth();
			tmp->m_H = tmp->GetImage()->GetHeight();
			tmp->m_ScaleX = scale;
			tmp->m_ScaleY = scale;
		}
	}
}

void Field::deleteField()
{
	if (this->field_size != 0)
	{
		delete[] this->field;
	}
}

void Field::updateButtons(bool initial)
{

	int element_size = g_pResources->getElementButton(0)->GetWidth();
	int padding = element_size / 10;
	int left_padding = (ORIG_WIDTH - ((element_size + padding) * BUTTONS_NUMBER - padding)) / 2;

	float scale = IwGxGetScreenWidth() / ORIG_WIDTH;

	for (int i = 0; i < BUTTONS_NUMBER; i++)
	{

		CSprite *tmp;
		if (initial)
		{
			tmp = new CSprite();
			tmp->SetImage(g_pResources->getElementButton(i));
			this->buttons[i] = tmp;
			AddChild(tmp);
		}
		else
		{
			tmp = this->buttons[i];
		}
		tmp->m_X = (left_padding + i * (element_size + padding)) * scale;
		tmp->m_Y = BUTTONS_TOP_PADDING * scale;
		tmp->m_W = tmp->GetImage()->GetWidth();
		tmp->m_H = tmp->GetImage()->GetHeight();
		tmp->m_ScaleX = scale;
		tmp->m_ScaleY = scale;
	}
}

void Field::deleteButtons()
{
	if (this->field_size != 0)
	{
		delete[] this->buttons;
	}
}

void Field::checkForInput()
{
	//Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && g_Input->isClick())
	{
		g_Input->Reset();
		for (int i = 0; i < BUTTONS_NUMBER; i++)
		{
			if (this->buttons[i]->HitTest(g_Input->GetX(), g_Input->GetY()))
			{
				this->p->removeColorFromStart(i+1);
			}
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
	for (int i = 0; i < this->field_size; i++)
		this->field[i] = NULL;
	this->buttons = new CSprite*[BUTTONS_NUMBER];

	// Do a first update on the field.
	this->updateField(true);

	// Add the buttons to the scene.
	this->updateButtons(true);
}

void Field::Exit()
{
	if (this->field_size != 0)
	{
		delete this->p;
		this->deleteField();
		this->deleteButtons();
		this->field_size = 0;
	}
}

void Field::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
	{
		return;
	}

	updateField();
	updateButtons();

	checkForInput();

	Scene::Update(deltaTime, alphaMul);
}

void Field::Render()
{
	Scene::Render();
}