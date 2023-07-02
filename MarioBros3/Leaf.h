#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF_RIGHT 16002
#define ID_ANI_LEAF_LEFT 16003

#define	LEAF_WIDTH 14
#define LEAF_BBOX_WIDTH 14
#define LEAF_BBOX_HEIGHT 14


class CLeaf : public CGameObject {
	float ax;
	float ay;
	float maxy;
	int idsprite;
	bool IsUp;
	bool IsRight;
	bool IsLeft;
	float rightmax = x + 32.0f;
	float rightmin = x;
public:
	CLeaf(){}
	CLeaf(float x, float y) : CGameObject(x, y) {
		maxy = y - 45;
		idsprite = ID_ANI_LEAF_RIGHT;
		IsUp = IsLeft =  false;
		IsRight = true;
		this->ax = 0;
		this->ay = 0.001f;
		this->vy = -0.5f;
		this->vx = 0;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

};


