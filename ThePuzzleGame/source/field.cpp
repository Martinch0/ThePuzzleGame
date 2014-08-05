#include "field.h"

void Field::updateField(bool initial)
{
	int max_x = p->getSizeX();
	int max_y = p->getSizeY();
	for (int y = 0; y < max_y; y++)
	{
		for (int x = 0; x < max_x; x++)
		{
			if (initial)
			{
				CSprite *tmp = new CSprite();
				tmp->SetImage(g_pResources->getElement(p->getElement(x, y)));
				tmp->m_X = x * tmp->GetImage()->GetWidth();
				tmp->m_Y = y * tmp->GetImage()->GetHeight();
				tmp->m_W = tmp->GetImage()->GetWidth();
				tmp->m_H = tmp->GetImage()->GetHeight();
				this->field[p->getIndex(x, y)] = tmp;
				AddChild(tmp);
			}
			else
			{

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

	Scene::Update(deltaTime, alphaMul);
}

void Field::Render()
{
	Scene::Render();
}