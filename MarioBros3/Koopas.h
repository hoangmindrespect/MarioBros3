#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_SPINNING_SPEED 0.3f


#define KOOPAS_BBOX_WIDTH 24
#define KOOPAS_BBOX_HEIGHT 36
#define KOOPAS_BBOX_HEIGHT_DIE 24

#define KOOPAS_DIE_TIMEOUT 5000

#define KOOPAS_STATE_WALKING_RIGHT 105
#define KOOPAS_STATE_WALKING_LEFT 106
#define KOOPAS_STATE_DIE_DOWN 205
#define KOOPAS_STATE_DIE_UP 206
#define KOOPAS_STATE_DIE_DOWN_KICKED 207
#define KOOPAS_STATE_DIE_UP_KICKED 208
#define KOOPAS_STATE_DIE_DOWN_SPIN 209
#define KOOPAS_STATE_DIE_UP_SPIN 210


#define ID_ANI_KOOPAS_WALKING_RIGHT 5052
#define ID_ANI_KOOPAS_WALKING_LEFT 5050

#define ID_ANI_KOOPAS_DIE_DOWN 5051
#define ID_ANI_KOOPAS_DIE_UP 5054
#define ID_ANI_KOOPAS_DIE_DOWN_SPIN 5053
#define ID_ANI_KOOPAS_DIE_UP_SPIN 5055

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	int n;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
	void setVx(float i) {
		vx = i;
	}
	void setVy(float i) {
		vy = i;
	}
};

