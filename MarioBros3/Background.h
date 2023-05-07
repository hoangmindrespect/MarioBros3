#pragma once

#include "GameObject.h"

class CBackground : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteId;

public:
	CBackground(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		spriteId = sprite_id;
	}
	int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CBackground* LPBACKGROUND;
