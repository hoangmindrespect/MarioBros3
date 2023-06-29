#pragma once

#include "GameObject.h"
#include "Coin.h"
#include "Animation.h"
#include "Animations.h"

#define FUNNEL_BBOX_WIDTH 32
#define FUNNEL_BBOX_HEIGHT 15


//1: coin, 2: item, 3: greenmushgroom
class CFunnel : public CGameObject {
	float x_target;
	float y_target;
public:
	CFunnel(float x, float y, float xt, float yt) : CGameObject(x, y) {
		x_target = xt;
		y_target = yt;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	float getXTarget() { return x_target; }
	float getYTarget() { return y_target; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};




