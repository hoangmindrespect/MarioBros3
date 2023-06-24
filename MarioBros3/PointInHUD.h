#pragma once
#include "GameObject.h"

#define POINTINHUD_WIDTH 56.0F
#define POINTINHUD_HEIGHT 7.0F

#define POINTINHUD_X_DEFAULT 68.0f

class CPointInHUD : public CGameObject
{
protected:
	
public:
	CPointInHUD(float x, float y) :CGameObject(x, y) {
		
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return 0; }
	void setPosition(float x, float y) { this->x = x; this->y = y; }
};

typedef CPointInHUD* LPPOINTINHUD;






