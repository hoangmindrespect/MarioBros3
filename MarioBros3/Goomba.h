#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.03f


#define GOOMBA_BBOX_WIDTH 18
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE_BY_KOOPAS 201
#define RED_GOOMBA_STATE_FLY_WALK	206
#define GOOMBA_STATE_DIE 200

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_DIE_BY_KOOPAS 5002

#define ID_ANI_RED_GOOMBA_WALKING 5003
#define ID_ANI_RED_GOOMBA_WING_RIGHT 5004
#define ID_ANI_RED_GOOMBA_WING_LEFT 5005
#define ID_ANI_RED_GOOMBA_DIE 5006
#define ID_ANI_RED_GOOMBA_DIE_BY_KOOPAS 5007

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	int type; // check type of goomba, red flying goomba or normal goomba
	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void SetYWhenCollideColorbox(LPGAMEOBJECT gameobject);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int t);
	virtual void SetState(int state);
};

