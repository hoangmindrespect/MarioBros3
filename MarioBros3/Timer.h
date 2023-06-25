#pragma once
#include "GameObject.h"

#define TIMER_WIDTH 24.0F
#define TIMER_HEIGHT 7.0F

#define TIMER_X_DEFAULT 140.0f

class CTimer : public CGameObject
{
protected:
	float time;
	float start;
public:
	CTimer(float x, float y) :CGameObject(x, y) {
		time = 300.0f; start = GetTickCount64() / 1000.0f;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return 0; }
	void setPosition(float x, float y) { this->x = x; this->y = y; }
};

typedef CTimer* LPTIMER;





