#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF_RIGHT 16002
#define ID_ANI_LEAF_LEFT 16003

#define	LEAF_WIDTH 24
#define LEAF_BBOX_WIDTH 24
#define LEAF_BBOX_HEIGHT 24

class CLeaf : public CGameObject {
	float maxy;
	int idsprite;
	bool IsUp;
	bool IsRight;
	bool IsLeft;
	float rightmax = x + 32.0f;
	float rightmin = x;
public:
	CLeaf(float x, float y) : CGameObject(x, y) {
		maxy = y - 45;
		idsprite = ID_ANI_LEAF_RIGHT;
		IsUp = IsLeft =  false;
		IsRight = true;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};


