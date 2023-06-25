#pragma once
#include "GameObject.h"

#define POWERFLYINGHUD_WIDTH 64.0F
#define POWERFLYINGHUD_HEIGHT 7.0F
#define POWERFLYINGHUD_X_DEFAULT 68.0f
#define ID_WHITE_ARROW 164024
#define ID_BLACK_ARROW 164025
#define ID_BUTTON_FLYING_MODE_BLACK	164027
#define ID_BUTTON_FLYING_MODE_WHITE	166024

class CPowerFlyingHUD : public CGameObject
{
protected:
	float time;
	float start;
public:
	CPowerFlyingHUD(float x, float y) :CGameObject(x, y) {
		time = 0.0f;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return 0; }
	void setPosition(float x, float y) { this->x = x; this->y = y; }
};

typedef CPowerFlyingHUD* LPPOWERFLYINGHUD;






