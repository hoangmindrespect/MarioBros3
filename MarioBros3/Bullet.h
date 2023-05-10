#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BULLET 15801

#define	BULLET_WIDTH 24
#define BULLET_BBOX_WIDTH 24
#define BULLET_BBOX_HEIGHT 24

class CBullet : public CGameObject {
	
public:
	CBullet(float x, float y, float vx, float vy) : CGameObject(x, y) {
		this->vx = vx;
		this->vy = vy;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};



