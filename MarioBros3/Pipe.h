#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CPipe : public CGameObject
{
protected:
	int height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdTop;
	int spriteIdBottom;

public:
	CPipe(float x, float y,
		float cell_width, float cell_height, int height, int s_top, int s_bottom) :CGameObject(x, y)
	{
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdTop = s_top;
		this->spriteIdBottom = s_bottom;
	}
	int IsBlocking() { return 1; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CPipe* LPPIPE;

