#pragma once

#include "GameObject.h"
#include "Mario.h"

#define TOP_EDGE_LIMIT	-88.0f
#define BOTTOM_EDGE_LIMIT	94.0f
#define VELOCITY_OPEN_CURTAIN	0.07f
#define VELOCITY_DROP_TITLE_GAME	0.3f

#define ID_OPEN_CURTAIN	166036
#define ID_DROP_TITLE_GAME	166038
#define ID_OPTION_ONE_PLAYER	166044
#define ID_OPTION_TWO_PLAYER	166045
#define ID_NUMBER_THREE	45431
//this class is implemented like a video
//ALL objects is arranged according to a predefined play
	//	1. Curtain will be open and drop title down
	//	2. Hanle collision [if press DIK_W at stage 2 -> skip this stage]: defend koopas fall into Mario,..
	//	3. User can press DIK_S to select option


class CIntro : public CGameObject { 
	// handle stage 1
	bool isCreateMario;
	bool isUp, isDown;
	bool flag;
	bool isFallDown;
	bool isCreateObject; // start stage 2
	ULONGLONG time_start;

	//object in intro
	CMario* red = new CMario();
	CMario* green = new CMario();
public:
	static bool isHitRed;

	CIntro(float x, float y) : CGameObject(x, y) {
		isUp = isDown = flag = isCreateMario = isHitRed = isFallDown = false;
		isCreateObject = false;
		time_start = GetTickCount64();
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool getIntoAni() { return isCreateObject; }
	int IsBlocking() { return 0; }
};



