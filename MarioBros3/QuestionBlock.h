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

	float miny = y - 26;
	float maxy = y;
	bool IsUp = false;
	bool IsDown = false;
public:
	CQuestionBlock(float x, float y, int z) : CGameObject(x, y) { 
		state = QUESTIONBLOCK_STATE_NONE_EMPTY;
		type = z;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	int getType() { return type; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};


