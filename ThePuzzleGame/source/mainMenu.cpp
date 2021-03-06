#include "mainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	Scene::Init();

	float scale = IwGxGetScreenWidth() / ORIG_WIDTH;

	// Create menu background
	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;

	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleX = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	// Create Start Game button
	float x_pos = IwGxGetScreenWidth() * 0.5f;
	float y_pos = IwGxGetScreenHeight() * 0.5f;
	playButton = new CSprite();
	playButton->SetImage(g_pResources->getPlayButton());
	playButton->m_X = x_pos;
	playButton->m_Y = y_pos;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 0.5f;
	playButton->m_AnchorY = 0.5f;
	playButton->m_ScaleX = scale;
	playButton->m_ScaleY = scale;
	AddChild(playButton);

	// Create HowToPlay Button
	howToPlayButton = new CSprite();
	howToPlayButton->SetImage(g_pResources->getHowToPlayButton());
	howToPlayButton->m_X = x_pos;
	howToPlayButton->m_Y = y_pos + (playButton->GetImage()->GetHeight() * scale);
	howToPlayButton->m_W = howToPlayButton->GetImage()->GetWidth();
	howToPlayButton->m_H = howToPlayButton->GetImage()->GetHeight();
	howToPlayButton->m_AnchorX = 0.5f;
	howToPlayButton->m_AnchorY = 0.5f;
	howToPlayButton->m_ScaleX = scale;
	howToPlayButton->m_ScaleY = scale;
	AddChild(howToPlayButton);
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
	{
		return;
	}

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && g_Input->isClick())
	{
		g_Input->Reset();
		if (playButton->HitTest(g_Input->GetX(), g_Input->GetY()))
		{
			// Switch to game scene
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("field"));
		}

		if (howToPlayButton->HitTest(g_Input->GetX(), g_Input->GetY()))
		{
			// Switch to HowToPlay scene
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("howtoplay"));
		}
	}
}

void MainMenu::Render()
{
	Scene::Render();
}