#pragma once

#include "GameObject.h"
#include "Koopas.h"

#define	KOOPAS_NAVIGATION_WIDTH 16.0f
class CKoopasNavigation : public CGameObject {
	CKoopas* koopas = NULL;
	bool isChangingDirection;
public:
	CKoopasNavigation(float x, float y) : CGameObject(x, y) {
		isChangingDirection = false;
	}
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void setHost(CKoopas* koo) { this->koopas = koo; }
};




