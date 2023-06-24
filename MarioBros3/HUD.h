#pragma once

#include "GameObject.h"
#define HUD_WIDTH 256.0f
// 
// The most popular type of object in Mario! 
// 
class CHUD : public CGameObject
{
protected:
	static CHUD* __instance;
	static float initialX;
	static float initialY;
public:
	CHUD(float x, float y) :CGameObject(x, y){}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	//void setPosition(float x, float y) { this->x = x; this->y = y; }
	int IsBlocking() { return 0; }
	static CHUD* GetInstance();
	void setPosition(float x, float y) { this->x = x; this->y = y; }
};

typedef CHUD* LPHUD;



