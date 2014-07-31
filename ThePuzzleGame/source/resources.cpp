#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
	//Load images
	
	Element = new CIw2DImage*[MAX_ELEMENT_TYPES - 1];
	Element[0] = Iw2DCreateImage("textures/ballblue.png");
	Element[1] = Iw2DCreateImage("textures/ballpurple.png");
	Element[2] = Iw2DCreateImage("textures/ballred.png");
	Element[3] = Iw2DCreateImage("textures/ballyellow.png");

	ElementDestroyed = Iw2DCreateImage("textures/balldestroyed.png");

	MenuBG = Iw2DCreateImage("textures/backgroundMenu.png");
	GameBG = Iw2DCreateImage("textures/backgroundGame.png");
	PlayButton = Iw2DCreateImage("textures/buttonPlay.png");
	
	ElementButton = new CIw2DImage*[MAX_ELEMENT_TYPES - 1];
	ElementButton[0] = Iw2DCreateImage("textures/buttonblue.png");
	ElementButton[1] = Iw2DCreateImage("textures/buttonpurple.png");
	ElementButton[2] = Iw2DCreateImage("textures/buttonred.png");
	ElementButton[3] = Iw2DCreateImage("textures/buttonyellow.png");
}

Resources::~Resources()
{
	for (int i = 0; i < MAX_ELEMENT_TYPES; i++)
	{
		delete Element[i];
	}
	delete[] Element;
	delete ElementDestroyed;
	delete MenuBG;
	delete GameBG;
	delete PlayButton;
	for (int i = 0; i < MAX_ELEMENT_TYPES; i++)
	{
		delete ElementButton[i];
	}
	delete[] ElementButton;
}

CIw2DImage** Resources::getElement()
{
	return Element;
}

CIw2DImage* Resources::getElementDestroyed()
{
	return ElementDestroyed;
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

CIw2DImage** Resources::getElementButton()
{
	return ElementButton;
}

//Global
Resources* g_pResources = 0;