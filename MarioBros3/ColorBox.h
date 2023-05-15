#pragma once
#pragma once

#include "GameObject.h"

class CColorBox : public CGameObject
{
public:
	float width;				// Unit: cell 
	int tmp = 0;
public:
	CColorBox(float x, float y,
		float width
		) :CGameObject(x, y)
	{
		this->width = width;
	}
	void Render();
	int IsCollidable() { return 1; };
	int IsBlocking() { return tmp; }
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

};

typedef CColorBox* LPCOLORBOX;

