#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "Leaf.h"
#include "Goomba.h"
#include "Koopas.h"
#define TOP_EDGE_LIMIT	-88.0f
#define BOTTOM_EDGE_LIMIT	94.0f
#define VELOCITY_OPEN_CURTAIN	0.07f
#define VELOCITY_DROP_TITLE_GAME	0.3f
#define COORDINATE_TO_CREATE_LU_MA	50.0f
#define COORDINATE_X_LUGIGI_JUMP	5.0f
#define TOP_EDGE_LIMIT_LUGIGI	10.0f

#define ID_OPEN_CURTAIN	166036
#define ID_DROP_TITLE_GAME	166038
#define ID_MAIN_SCREEN_INTRO	166039
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
	bool isFallOntoMario;
	bool isCreateObject; 
	bool isShaked;
	// start stage 2
	bool isChangeDirection;
	bool isWaitedLugigi;
	bool isLugigiThrowShell;
	bool isFaceToFaceLugigi;
	bool isMarioHitKoopas;
	bool isKoopasChangedDirection;
	bool isSmallChangedDirectFirst;
	bool isSmallChangedDirectSecond;

	ULONGLONG time_start;
	ULONGLONG bracing_start;
	//object in intro
	CMario* red = NULL;
	CMario* green = NULL;
	CLeaf* leaf = NULL;
	CGoomba* goo = NULL;
	CKoopas* second_koopas = NULL;
	CKoopas* first_koopas = NULL;
public:
	static bool isHitMario;
	static bool isChooseOptionOne;
	static bool isChooseOptionTwo;
	static bool isDoneStageTwo;

	CIntro(float x, float y) : CGameObject(x, y) {
		isUp = isDown = flag = isCreateMario = isFallOntoMario = isShaked =  false;
		isCreateObject = isChangeDirection = isWaitedLugigi = isFaceToFaceLugigi = isLugigiThrowShell = false;
		isMarioHitKoopas = isKoopasChangedDirection = isSmallChangedDirectFirst = isSmallChangedDirectSecond = isDoneStageTwo= false;

		isChooseOptionOne = false;
		isChooseOptionTwo = false;
		time_start = GetTickCount64();
		bracing_start = 0;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool getIntoAni() { return isCreateObject; }
	int IsBlocking() { return 0; }

	bool getOptionOne() { return isChooseOptionOne; }
	bool getOptionTwo() { return isChooseOptionTwo; }

	void getOptionOne(bool a) { isChooseOptionOne = a; }
	void getOptionTwo(bool a) { isChooseOptionTwo = a; }
};



