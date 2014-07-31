#include "mainMenu.h"
#include "IwGx.h"
#include "input.h"
#include <iostream> //FOR TESTING

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	Scene::Init();

	//Create Start Game button
	float y_pos = (float)IwGxGetScreenHeight() * 0.5f;
	playButton = new CSprite();
	//playButton->SetImage(image);
	playButton->m_X = IwGxGetScreenWidth() / 2.0f;
	playButton->m_Y = y_pos;
	playButton->m_W = 100;//playButton->GetImage()->GetWidth();
	playButton->m_H = 100;//playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 0.5f;
	playButton->m_AnchorY = 0.5f;
	playButton->m_ScaleX = 1.5f;
	playButton->m_ScaleY = 1.5f;
	AddChild(playButton);

	std::cout << "INIT" << std::endl;
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
	{
		return;
	}

	Scene::Update(deltaTime, alphaMul);

	//Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && g_Input->isClick())
	{
		g_Input->Reset();
		if (playButton->HitTest(g_Input->GetX(), g_Input->GetY()))
		{
			//Switch to game scene
			//for now just a test
			std::cout << "CLICK" << std::endl;
		}
	}
}

void MainMenu::Render()
{
	Scene::Render();
}