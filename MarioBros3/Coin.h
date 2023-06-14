#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11900

#define	COIN_WIDTH 16
#define COIN_BBOX_WIDTH 16
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
	float maxy;
	float miny;
	bool IsUp;
	bool IsDown;
	int isInQuestionBlock;
public:
	CCoin(float x, float y, int k) : CGameObject(x, y) {
		maxy = y - 55;
		miny = y - 25;
		IsUp = IsDown = false;
		isInQuestionBlock = k;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};


