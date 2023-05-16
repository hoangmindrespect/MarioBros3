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



//1: coin, 2: redmush, 3: greenmush, 4: leaf
class CQuestionBlock : public CGameObject {
	int type;//1: coin, 2: redmush, 3: greenmush, 4: leaf
	int direction; //1: vertical, 2: horizontal

	float miny = y - 26;
	float maxy = y;
	bool IsUp = false; // => Is use for vertical question block
	bool IsDown = false;// => Is use for vertical questionblock

	int option = 1; // check mario is on right or left
	bool IsMoveRight = false; // => Is use for horizontal question block
	bool IsMoveLeft = false;// => Is use for horizontal question block
	float xmax1 = x + 32; float xmin = x;
	float xmax2 = x - 32;

public:
	CQuestionBlock(float x, float y, int z, int t) : CGameObject(x, y) { 
		state = QUESTIONBLOCK_STATE_NONE_EMPTY;
		type = z;
		direction = t;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	int getType() { return type; }
	void setOption(int i) { option = i; }
	int getDirection() { return direction; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};


