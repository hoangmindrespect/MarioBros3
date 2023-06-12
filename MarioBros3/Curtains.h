#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


class CCurtains : public CGameObject {
	BOOLEAN isUp, isDown;
	BOOLEAN flag;
	BOOLEAN intoAni;
	ULONGLONG time_shaking;
public:
	CCurtains(float x, float y) : CGameObject(x, y) {
		isUp = isDown = flag = false;
		intoAni = false;
		time_shaking = 0;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking() { return 0; }
};



