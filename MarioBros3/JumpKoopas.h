#pragma once

#include "GameObject.h"

#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_WALKING_SPEED 0.03f
#define KOOPAS_SPINNING_SPEED 0.2f


#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 25
#define KOOPAS_BBOX_HEIGHT_DIE 13

#define KOOPAS_DIE_TIMEOUT 5000

#define JUMP_KOOPAS_STATE_JUMPING 111222

#define JUMP_KOOPAS_STATE_WALKING_RIGHT 100005
#define JUMP_KOOPAS_STATE_WALKING_LEFT 100006

#define JUMP_KOOPAS_STATE_DIE_DOWN 200005
#define JUMP_KOOPAS_STATE_DIE_UP 200006

#define JUMP_KOOPAS_STATE_DIE_DOWN_SPIN 200009
#define JUMP_KOOPAS_STATE_DIE_UP_SPIN 200010

#define JUMP_KOOPAS_STATE_IS_HOLD_DOWN 200011
#define JUMP_KOOPAS_STATE_IS_HOLD_UP 200012

#define JUMP_KOOPAS_STATE_RETURN_DOWN 200015
#define JUMP_KOOPAS_STATE_RETURN_UP 200017

#define ID_ANI_GREEN_KOOPAS_MOVING_RIGHT 5067
#define ID_ANI_GREEN_KOOPAS_MOVING_LEFT 5066

#define ID_ANI_GREEN_KOOPAS_WALKING_RIGHT 5059
#define ID_ANI_GREEN_KOOPAS_WALKING_LEFT 5058

#define ID_ANI_GREEN_KOOPAS_DIE_DOWN 5060
#define ID_ANI_GREEN_KOOPAS_DIE_UP 5062

#define ID_ANI_GREEN_KOOPAS_DIE_DOWN_SPIN 5061
#define ID_ANI_GREEN_KOOPAS_DIE_UP_SPIN 5063

#define ID_ANI_GREEN_KOOPAS_RETURN_DOWN 5064
#define ID_ANI_GREEN_KOOPAS_RETURN_UP 5065	

class CJumpKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG die_start;
	ULONGLONG return_start;
	ULONGLONG jumping_start;
	bool shaking;
	bool isJumping;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CJumpKoopas(float x, float y);
	virtual void SetState(int state);
	void setVx(float i) {
		vx = i;
	}
	void setVy(float i) {
		vy = i;
	}
	void setX(float x) {
		this->x = x;
	}
	void setY(float x) {
		this->y = x;
	}
	
	ULONGLONG getDieStart() { return die_start; }
	ULONGLONG getReturnStart() { return return_start; }
	int getnx() { return nx; }
};

