#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CHUD : public CGameObject
{
protected:
public:
	CHUD(float x, float y) :CGameObject(x, y)
	{}

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return 0; }
};

typedef CHUD* LPHUD;



