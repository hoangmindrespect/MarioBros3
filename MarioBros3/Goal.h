#pragma once
#include "GameObject.h"

#define GOAL_WIDTH 16
#define ID_FLOWER	16005
#define ID_STAR	16004
#define ID_MUSHROOOM	16000
#define ANI_ID_FLOWER	160989
#define ANI_ID_STAR	160990
#define ANI_ID_MUSHROOOM	160988
class CGoal : public CGameObject
{
protected:
	BOOLEAN isFlower;
	BOOLEAN isStar;
	BOOLEAN isMushroom;
	BOOLEAN isCollide;
	ULONGLONG time_showing;
public:
	CGoal(float x, float y) :CGameObject(x, y)
	{
		isFlower = true; time_showing = GetTickCount64();
		isStar = isMushroom = isCollide = false;
	}

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void setIsCollide(bool a) { isCollide = a; }
	int getResult() {
		if (isStar)
			return 1;
		else if (isMushroom)
			return 2;
		else if (isFlower)
			return 3;
		else
			return 0;
	}

};

typedef CGoal* LPGOAL;


