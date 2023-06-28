
#pragma once
#include "GameObject.h"
#define RED_GOOMBA_WINGS_BBOX_WIDTH 20
#define RED_GOOMBA_WINGS_BBOX_HEIGHT 24
#define RED_GOOMBA_BBOX_WIDTH 18
#define RED_GOOMBA_BBOX_HEIGHT 16
#define RED_GOOMBA_BBOX_HEIGHT_DIE 7

#define RED_GOOMBA_GRAVITY 0.001f
#define RED_GOOMBA_WALKING_SPPED 0.03f
#define RED_GOOMBA_JUMPING_SPEED 0.1f

#define RED_GOOMBA_STATE_WALKING_WITH_WINGS	555555
#define RED_GOOMBA_STATE_PREPARING_WITH_WINGS	555559
#define RED_GOOMBA_STATE_JUMPING_WITH_WINGS	555560

#define RED_GOOMBA_STATE_WALKING_NONE_WINGS 555556
#define RED_GOOMBA_STATE_DIE 555557
#define RED_GOOMBA_STATE_DIE_BY_KOOPAS 555558

#define ID_RED_GOOMBA_WALKING_NOT_JUMP	5003
#define ID_RED_GOOMBA_WALKING_JUMP	5004
#define ID_RED_GOOMBA_WALKING 5025
#define ID_RED_GOOMBA_DIE 5006
class CRedGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG die_start;
	ULONGLONG time_For_Action;
	// red goomba has three action when moving:
	BOOLEAN isNotJump;
	BOOLEAN isPrepare;
	BOOLEAN isJump;
	int countPre; // đếm số lần chuẩn bị nhảy
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CRedGoomba(float x, float y);
	virtual void SetState(int state);
};


