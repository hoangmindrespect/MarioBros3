#pragma once
#include "GameObject.h"

#define TIMER_WIDTH 24.0F
#define TIMER_HEIGHT 7.0F
#define TIMER_X_DEFAULT 140.0f
#define TIMER_Y_HIDDEN	400.0f
#define ID_FONT_NUMBER_ZERO	164012
#define ID_FONT_NUMBER_ONE	164013
#define ID_FONT_NUMBER_TWO	164014
#define ID_FONT_NUMBER_THREE	164015
#define ID_FONT_NUMBER_FOUR	164016
#define ID_FONT_NUMBER_FIVE	164017
#define ID_FONT_NUMBER_SIX	164018
#define ID_FONT_NUMBER_SEVEN	164019
#define ID_FONT_NUMBER_EIGHT	164020
#define ID_FONT_NUMBER_NINE	164021
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





