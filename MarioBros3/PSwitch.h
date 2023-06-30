#pragma once

#include "GameObject.h"
#include "Coin.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PSWITCH 15440
#define ID_ANI_PSWITCH_CLICKED 15450
#define PSWITCH_STATE_NORMAL	13244
#define PSWITCH_STATE_CLICKED	13245

#define	PSWITCH_WIDTH 16
#define PSWITCH_BBOX_WIDTH 16
#define PSWITCH_BBOX_HEIGHT 16



//1: coin, 2: item, 3: greenmushgroom
class CPSwitch : public CGameObject {
public:
	CPSwitch(float x, float y) : CGameObject(x, y) {
		state = PSWITCH_STATE_NORMAL;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};



