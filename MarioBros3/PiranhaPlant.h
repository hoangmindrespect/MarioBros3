#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Bullet.h"
#define ID_ANI__PIRANHA_UP_LEFT 15600
#define ID_ANI__PIRANHA_DOWN_LEFT 15500
#define ID_ANI__PIRANHA_UP_RIGHT 15800
#define ID_ANI__PIRANHA_DOWN_RIGHT 15700

#define ID_ANI__PIRANHA_UP_LEFT1 15605
#define ID_ANI__PIRANHA_DOWN_LEFT1 15505
#define ID_ANI__PIRANHA_UP_RIGHT1 15805
#define ID_ANI__PIRANHA_DOWN_RIGHT1 15705

#define ID_ANI__PIRANHA_DOWN_UP 15865


#define PIRANHA_BBOX_WIDTH 16
#define PIRANHA_BBOX_HEIGHT 32
#define PIRANHA_BBOX_BITE_HEIGHT 25

#define PIRANHA_STATE_UP_LEFT 64
#define	PIRANHA_STATE_DOWN_LEFT 27
#define	PIRANHA_STATE_UP_RIGHT 65
#define	PIRANHA_STATE_DOWN_RIGHT 56

#define	PIRANHA_STATE_BITE 112

class CPiranhaPlant : public CGameObject {
	int model; // red, green, bite
	float ymax;
	float ymax1;
	bool IsStart_Fire;
	bool IsStart_Up;
	bool IsStart_Down;
	ULONGLONG timeStart_Fire;
	ULONGLONG timeStart_Up;
	ULONGLONG timeStart_Down;
public:
	CPiranhaPlant(float x, float y, int model) : CGameObject(x, y) {
		ymax = y - 41.0f;
		ymax1 = x - 33.0f;
		this->model = model;
		IsStart_Down = false;
		IsStart_Fire = false;
		IsStart_Up = true; // at the first time meet mario it up immediately!
		state = PIRANHA_STATE_UP_LEFT;
		timeStart_Fire = timeStart_Up = timeStart_Down = 1;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	friend void KeepMoving(CPiranhaPlant* a);

};





