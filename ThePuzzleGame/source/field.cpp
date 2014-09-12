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
			tmp->m_Y = (FIELD_TOP_PADDING + y * (tmp->GetImage()->GetHeight() + field_padding)) * scale;
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

	CSprite *tmp;

	// Add element buttons
	for (int i = 0; i < BUTTONS_NUMBER; i++)
	{
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

	// Add top buttons
	if (initial)
	{
		pauseButton = new CSprite();
		pauseButton->SetImage(g_pResources->getPauseButton());
		AddChild(pauseButton);
		restartButton = new CSprite();
		restartButton->SetImage(g_pResources->getRestartButton());
		AddChild(restartButton);

	}
	pauseButton->m_X = 0 * scale;
	pauseButton->m_Y = 0 * scale;
	pauseButton->m_W = pauseButton->GetImage()->GetWidth();
	pauseButton->m_H = pauseButton->GetImage()->GetHeight();
	pauseButton->m_ScaleX = scale;
	pauseButton->m_ScaleY = scale;

	restartButton->m_X = 150 * scale;
	restartButton->m_Y = 0 * scale;
	restartButton->m_W = restartButton->GetImage()->GetWidth();
	restartButton->m_H = restartButton->GetImage()->GetHeight();
	restartButton->m_ScaleX = scale;
	restartButton->m_ScaleY = scale;
}

void Field::deleteButtons()
{
	if (this->field_size != 0)
	{
		delete[] this->buttons;
	}
}

void Field::updateScore(bool initial)
{
	float scale = IwGxGetScreenWidth() / ORIG_WIDTH;

	if (initial)
	{
		this->turnsLeft = new CLabel();
		this->turnsLeft->m_X = (ORIG_WIDTH - 300) * scale;
		this->turnsLeft->m_Y = 20 * scale;
		this->turnsLeft->m_H = 30;
		this->turnsLeft->m_W = 250;
		this->turnsLeft->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
		this->turnsLeft->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
		this->turnsLeft->m_Font = g_pResources->getFont();
		this->turnsLeft->m_ScaleX = scale;
		this->turnsLeft->m_ScaleY = scale;
		AddChild(this->turnsLeft);

		this->gameOver = new CLabel();
		this->gameOver->m_X = ((ORIG_WIDTH - 300) / 2) * scale;
		this->gameOver->m_Y = 350 * scale;
		this->gameOver->m_H = 30;
		this->gameOver->m_W = 300;
		this->gameOver->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
		this->gameOver->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
		this->gameOver->m_Font = g_pResources->getFont();
		this->gameOver->m_ScaleX = scale;
		this->gameOver->m_ScaleY = scale;
		this->gameOver->m_IsVisible = false;
		AddChild(this->gameOver);
	}
	char str[16];
	snprintf(str, 16, "Turns left: %d", this->p->getTurnsLeft());
	this->turnsLeft->m_Text = str;

	if (this->state == STATE_LOST)
	{
		this->gameOver->m_Text = "You Lost";
	}
	else if (this->state == STATE_WON)
	{
		this->gameOver->m_Text = "You Won";
	}
	else
	{
		this->gameOver->m_Text = "";
	}
}

void Field::updateGameState()
{
	if (this->state != STATE_WON || this->state != STATE_LOST)
	{
		bool solved = this->p->isSolved();
		int turnsLeft = this->p->getTurnsLeft();
		if (solved && turnsLeft >= 0)
		{
			this->gameOver->m_IsVisible = true;
			this->state = STATE_WON;
		}
		else if (!solved && turnsLeft <= 0)
		{
			this->gameOver->m_IsVisible = true;
			this->state = STATE_LOST;
		}
	}
}

void Field::checkForInput()
{
	//Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && g_Input->isClick())
	{
		g_Input->Reset();

		// handle input relatively to the current state of the game.
		switch (this->state)
		{
		case STATE_PLAYING:
			for (int i = 0; i < BUTTONS_NUMBER; i++)
			{
				if (this->buttons[i]->HitTest(g_Input->GetX(), g_Input->GetY()))
				{
					this->p->removeColorFromStart(i + 1);
					break;
				}
			}
			if (this->restartButton->HitTest(g_Input->GetX(), g_Input->GetY()))
			{
				this->reset();
			}
			break;
		case STATE_LOST:
		case STATE_WON:
			if (this->restartButton->HitTest(g_Input->GetX(), g_Input->GetY()))
			{
				this->reset();
			}
			break;
		}
	}
}

void Field::reset()
{
	this->gameOver->m_IsVisible = false;
	this->p->revert();
	this->state = STATE_PLAYING;
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
	
	// Set the state to playing
	this->state = STATE_PLAYING;

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

	this->updateScore(true);
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
	this->updateGameState();
	this->updateField();
	this->updateButtons();
	this->updateScore();

	this->checkForInput();

	Scene::Update(deltaTime, alphaMul);
}

void Field::Render()
{
	Scene::Render();
}