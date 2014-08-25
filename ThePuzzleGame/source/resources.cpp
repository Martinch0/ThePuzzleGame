#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
	//Load images
	
	Element = new CIw2DImage*[MAX_ELEMENT_TYPES];
	Element[0] = Iw2DCreateImage("textures/balldestroyed.png");
	Element[1] = Iw2DCreateImage("textures/glass-sd.png");
	Element[2] = Iw2DCreateImage("textures/rock-sd.png");
	Element[3] = Iw2DCreateImage("textures/metal-sd.png");
	Element[4] = Iw2DCreateImage("textures/wood-sd.png");

	MenuBG = Iw2DCreateImage("textures/backgroundMenu.png");
	GameBG = Iw2DCreateImage("textures/backgroundGame.png");
	PlayButton = Iw2DCreateImage("textures/buttonPlay.png");
	HowToPlayButton = Iw2DCreateImage("textures/buttonHowToPlay.png");
	BackButton = Iw2DCreateImage("textures/buttonBack.png");
	
	ElementButton = new CIw2DImage*[MAX_ELEMENT_TYPES - 1];
	ElementButton[0] = Iw2DCreateImage("textures/buttonglass.png");
	ElementButton[1] = Iw2DCreateImage("textures/buttonrock.png");
	ElementButton[2] = Iw2DCreateImage("textures/buttonmetal.png");
	ElementButton[3] = Iw2DCreateImage("textures/buttonwood.png");
}

Resources::~Resources()
{
	for (int i = 0; i < MAX_ELEMENT_TYPES; i++)
	{
		delete Element[i];
	}
	delete[] Element;
	delete MenuBG;
	delete GameBG;
	delete PlayButton;
	delete HowToPlayButton;
	delete BackButton;
	for (int i = 0; i < MAX_ELEMENT_TYPES - 1; i++)
	{
		delete ElementButton[i];
	}
	delete[] ElementButton;
}

CIw2DImage** Resources::getElements()
{
	return Element;
}

CIw2DImage* Resources::getElement(int p)
{
	return Element[p];
}

CIw2DImage* Resources::getMenuBG()
{
	return MenuBG;
}

CIw2DImage* Resources::getGameBG()
{
	return GameBG;
}

CIw2DImage* Resources::getPlayButton()
{
	return PlayButton;
}

CIw2DImage* Resources::getHowToPlayButton()
{
	return HowToPlayButton;
}

CIw2DImage* Resources::getBackButton()
{
	return BackButton;
}

CIw2DImage* Resources::getElementButton(int p)
{
	return ElementButton[p];
}

CIw2DImage** Resources::getElementButtons()
{
	return ElementButton;
}

//Global
Resources* g_pResources = 0;