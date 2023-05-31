#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GRASS 25900

#define	GRASS_WIDTH 16
#define GRASS_BBOX_WIDTH 16
#define GRASS_BBOX_HEIGHT 16

class CGrassInMap : public CGameObject {
	
public:
	CGrassInMap(float x, float y) : CGameObject(x, y) {
	}
	void Render();
	//void Update(DWORD dt);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};


