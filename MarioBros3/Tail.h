#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH 12
#define TAIL_BBOX_HEIGHT 7

#define TAIL_STATE_ATTACK	89765
#define TAIL_STATE_NONE_ATTACK	89767

class CTail : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
public:
	CTail(float x, float y);
	virtual void SetState(int state);
};


