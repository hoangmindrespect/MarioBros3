#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK1 10101
#define ID_ANI_BRICK2 10202
#define ID_ANI_BRICK3 10203

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 17
#define BRICK_BBOX_HEIGHT 15

class CBrick : public CGameObject {
	int model;
	bool isHitBySmall;

	float miny = y - 10;
	float maxy = y;
	bool IsUp = false;
	bool IsDown = false;
public:
	CBrick(float x, float y, int mo) : CGameObject(x, y) { this->model = mo; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int getModel() { return model; }
	void SetIsHitBySmall(bool a) { isHitBySmall = a; }
};

