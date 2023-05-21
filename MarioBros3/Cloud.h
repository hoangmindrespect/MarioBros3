#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CCloud : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin1, spriteIdMiddle1, spriteIdEnd1, spriteIdBegin2, spriteIdMiddle2, spriteIdEnd2;
public:
	CCloud(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin1, int sprite_id_middle1, int sprite_id_end1,
		int sprite_id_begin2, int sprite_id_middle2, int sprite_id_end2 ) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin1 = sprite_id_begin1;
		this->spriteIdMiddle1 = sprite_id_middle1;
		this->spriteIdEnd1 = sprite_id_end1;
		this->spriteIdBegin2 = sprite_id_begin2;
		this->spriteIdMiddle2 = sprite_id_middle2;
		this->spriteIdEnd2 = sprite_id_end2;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CCloud* LPCLOUD;

