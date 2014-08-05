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
	CIw2DImage** ElementButton;

public:
	CIw2DImage** getElements();
	CIw2DImage* getElement(int p);
	CIw2DImage* getMenuBG();
	CIw2DImage* getGameBG();
	CIw2DImage* getPlayButton();
	CIw2DImage** getElementButton();

public:
	Resources();
	~Resources();
};

extern Resources* g_pResources;


#endif