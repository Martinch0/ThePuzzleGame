#include "HowToPlay.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"

HowToPlay::HowToPlay()
{
}

HowToPlay::~HowToPlay()
{
}

void HowToPlay::Init()
{
	Scene::Init();

	//Create menu background
	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	//Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleX = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	//Create Back button
	backButton = new CSprite();
	backButton->SetImage(g_pResources->getBackButton());
	backButton->m_X = IwGxGetScreenWidth() / 2.0f;
	backButton->m_Y = (float)IwGxGetScreenHeight() - (backButton->GetImage()->GetHeight() * 0.1f);
	backButton->m_W = backButton->GetImage()->GetWidth();
	backButton->m_H = backButton->GetImage()->GetHeight();
	backButton->m_AnchorX = 0.5f;
	backButton->m_AnchorY = 0.5f;
	backButton->m_ScaleX = 0.2f;
	backButton->m_ScaleY = 0.2f;
	AddChild(backButton);
}

void HowToPlay::Update(float deltaTime, float alphaMul)
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
		if (backButton->HitTest(g_Input->GetX(), g_Input->GetY()))
		{
			//Switch to game scene
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("mainmenu"));
		}
	}
}

void HowToPlay::Render()
{
	Scene::Render();
}