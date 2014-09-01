#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#define MAX_ELEMENT_TYPES 5

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

class Resources
{
protected:
	CIw2DImage** Element;
	CIw2DImage* MenuBG;
	CIw2DImage* GameBG;
	CIw2DImage* PlayButton;
	CIw2DImage* HowToPlayButton;
	CIw2DImage* BackButton;
	CIw2DImage** ElementButton;
	CIw2DImage* RestartButton;
	CIw2DImage* PauseButton;
	CIw2DFont* Font;

public:
	CIw2DImage** getElements();
	CIw2DImage* getElement(int p);
	CIw2DImage* getMenuBG();
	CIw2DImage* getGameBG();
	CIw2DImage* getPlayButton();
	CIw2DImage* getHowToPlayButton();
	CIw2DImage* getBackButton();
	CIw2DImage* getElementButton(int p);
	CIw2DImage** getElementButtons();
	CIw2DImage* getRestartButton();
	CIw2DImage* getPauseButton();
	CIw2DFont* getFont();

public:
	Resources();
	~Resources();
};

extern Resources* g_pResources;


#endif