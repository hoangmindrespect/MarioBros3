#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11900
#define ID_ANI_COIN_NOT_ROTATE 11901

#define	COIN_WIDTH 16
#define COIN_BBOX_WIDTH 16
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
	float maxy;
	float miny;
	bool IsUp;
	bool IsDown;
	int type; // 1. coin in questionblock, 2. coin rotate ,3. coin not rotate
public:
	CCoin(float x, float y, int k) : CGameObject(x, y) {
		maxy = y - 55;
		miny = y - 25;
		IsUp = IsDown = false;
		type = k;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};


