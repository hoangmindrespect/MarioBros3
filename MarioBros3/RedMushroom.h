#pragma once
#include "GameObject.h"

#define REDMUSHROOM_GRAVITY 0.002f
#define REDMUSHROOM_WALKING_SPEED 0.1f


#define REDMUSHROOM_BBOX_WIDTH 16
#define REDMUSHROOM_BBOX_HEIGHT 15

class CRedMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float ymax;
	BOOLEAN isOut;
	float miny = y - 10;
	float maxy = y;
	bool IsUp = false; 
	bool IsDown = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void setay(float a) { ay = a; }
	void setvx(float a) { vx = a; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CRedMushroom(float x, float y);
};


