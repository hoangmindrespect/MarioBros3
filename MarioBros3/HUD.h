#pragma once

#include "GameObject.h"
#define HUD_WIDTH 256.0f
#define HUD_HEIGHT 48.0f
#define HUD_Y_HIDDEN 403.0f
#define HUD_Y_DEFAULT 211.0f

// 
// The most popular type of object in Mario! 
// 
class CHUD : public CGameObject
{
protected:
public:
	CHUD(float x, float y) :CGameObject(x, y){}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return 0; }
	void setPosition(float x, float y) { this->x = x; this->y = y; }
};

typedef CHUD* LPHUD;



