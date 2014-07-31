#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#define MAX_ELEMENT_TYPES 4

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

class Resources
{
protected:
	CIw2DImage** Element;
	CIw2DImage* ElementDestroyed;
	CIw2DImage* MenuBG;
	CIw2DImage* GameBG;
	CIw2DImage* PlayButton;
	CIw2DImage** ElementButton;

public:
	CIw2DImage** getElement();
	CIw2DImage* getElementDestroyed();
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