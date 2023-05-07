#pragma once
#pragma once

#include "GameObject.h"

class CColorBox : public CGameObject
{
public:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteId;
	int tmp = 0;
public:
	CColorBox(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		spriteId = sprite_id;
	}
	void Render();
	int IsCollidable() { return 1; };
	int IsBlocking() { return tmp; }
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CColorBox* LPCOLORBOX;

