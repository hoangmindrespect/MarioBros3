#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Bullet.h"
#define ID_ANI__PIRANHA_UP_LEFT 15600
#define ID_ANI__PIRANHA_DOWN_LEFT 15500
#define ID_ANI__PIRANHA_UP_RIGHT 15800
#define ID_ANI__PIRANHA_DOWN_RIGHT 15700

#define PIRANHA_BBOX_WIDTH 24
#define PIRANHA_BBOX_HEIGHT 48

#define PIRANHA_STATE_UP_LEFT 64
#define	PIRANHA_STATE_DOWN_LEFT 27
#define	PIRANHA_STATE_UP_RIGHT 65
#define	PIRANHA_STATE_DOWN_RIGHT 56


class CPiranhaPlant : public CGameObject {
	float ymax;
	bool IsUp;
	bool IsFire;
	//vector<CBullet*> bullet;
public:
	CPiranhaPlant(float x, float y) : CGameObject(x, y) {
		ymax = y - 47.0f;
		IsUp = false;
		IsFire = false;
		state = PIRANHA_STATE_UP_LEFT;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};





