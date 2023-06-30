#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BROKE_BRICK	35201
#define ID_ANI_SMALL_TO_BIG_LEFT 35203
#define ID_ANI_SMALL_TO_BIG_RIGHT 35202
#define ID_ANI_POINT_PLUS_100 166022
#define ID_ANI_POINT_PLUS_1000 166023
#define ID_ANI_ATTACK	35205
#define ID_YELLOW_GOOMBA_DIE_EFFECT	35516
#define ID_RED_GOOMBA_DIE_EFFECT	35517
#define ID_RED_ONE_UP	166025
class CEffect : public CGameObject {
	int type;
	float ax;
	float ay;
	float top;
	ULONGLONG time_start;
public:
	CEffect(float x, float y, int k);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);

	int IsBlocking() { return 0; }
};




