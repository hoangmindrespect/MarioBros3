#pragma once

#include "GameObject.h"
#include "Coin.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTIONBLOCK 15000
#define ID_ANI_QUESTIONBLOCK_EMPTY 15900

#define QUESTIONBLOCK_STATE_NONE_EMPTY 300
#define QUESTIONBLOCK_STATE_EMPTY 409

#define	QUESTIONBLOCK_WIDTH 24
#define QUESTIONBLOCK_BBOX_WIDTH 24
#define QUESTIONBLOCK_BBOX_HEIGHT 24


//type: 
//1: coin, 2: redmush, 3: greenmush
class CQuestionBlock : public CGameObject {
	int type;

	float miny = y - 6;
	float maxy = y;
	bool IsUp = false;
	bool IsDown = false;

	float xo, yo;
	float minyo = y - 85;
	float maxyo = y - 45;
	bool IsUpObj = false;
	bool IsDownObj = false;
public:
	LPGAMEOBJECT obj = nullptr;
	CQuestionBlock(float x, float y, int z) : CGameObject(x, y) { 
		type = z;
		this->xo = x;
		this->yo = y - 25;
		
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	int getType() { return type; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

};


