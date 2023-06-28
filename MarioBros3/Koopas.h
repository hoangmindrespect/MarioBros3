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
#define KOOPAS_STATE_WALKING_RIGHT 105
#define KOOPAS_STATE_WALKING_LEFT 106
#define KOOPAS_STATE_DIE_DOWN 205
#define KOOPAS_STATE_DIE_UP 206
#define KOOPAS_STATE_DIE_DOWN_SPIN 209
#define KOOPAS_STATE_DIE_UP_SPIN 210
#define KOOPAS_STATE_IS_HOLD_DOWN 211
#define KOOPAS_STATE_IS_HOLD_UP 212
#define KOOPAS_STATE_RETURN_DOWN 215
#define KOOPAS_STATE_RETURN_UP 217

#define ID_ANI_GREEN_KOOPAS_MOVING_RIGHT 5067
#define ID_ANI_GREEN_KOOPAS_MOVING_LEFT 5066

#define ID_ANI_KOOPAS_WALKING_RIGHT 5052
#define ID_ANI_KOOPAS_WALKING_LEFT 5050

#define ID_ANI_KOOPAS_DIE_DOWN 5051
#define ID_ANI_KOOPAS_DIE_UP 5054
#define ID_ANI_KOOPAS_DIE_DOWN_SPIN 5053
#define ID_ANI_KOOPAS_DIE_UP_SPIN 5055

#define ID_ANI_KOOPAS_RETURN_DOWN 5056
#define ID_ANI_KOOPAS_RETURN_UP 5057


#define ID_ANI_GREEN_KOOPAS_WALKING_RIGHT 5059
#define ID_ANI_GREEN_KOOPAS_WALKING_LEFT 5058

#define ID_ANI_GREEN_KOOPAS_DIE_DOWN 5060
#define ID_ANI_GREEN_KOOPAS_DIE_UP 5062
#define ID_ANI_GREEN_KOOPAS_DIE_DOWN_SPIN 5061
#define ID_ANI_GREEN_KOOPAS_DIE_UP_SPIN 5063

#define ID_ANI_GREEN_KOOPAS_RETURN_DOWN 5064
#define ID_ANI_GREEN_KOOPAS_RETURN_UP 5065	
class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	int type; // 1 red 2 green 3 jump
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

	void OnCollisionWithGoomBa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y, int color);
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

