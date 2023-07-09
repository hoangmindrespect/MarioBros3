#pragma once
#include "GameObject.h"
#include "Goal.h"
#define CARD_X_DEFAULT	183.0f
#define CARD_Y_DEFAULT	203.0f
#define CARD_Y_HIDDEN	-292.0f

#define CARD_STATE_EMPTY	2508
#define CARD_STATE_FLICKING_MUSH	2509
#define CARD_STATE_FLICKING_FLOW	2510
#define CARD_STATE_FLICKING_STAR	2511

#define CARD_STATE_MUSH_STATIC	25990
#define CARD_STATE_FLOW_STATIC	25991
#define CARD_STATE_STAR_STATIC	25992

#define ID_CARD_EMPTY	166032
#define ID_CARD_MUSHROOM_FLICKING	166026
#define ID_CARD_FLOWER_FLICKING	166027
#define ID_CARD_STAR_FLICKING	166028
#define ID_CARD_MUSHROOM	136029
#define ID_CARD_FLOWER	136030
#define ID_CARD_STAR	136031
class CCard : public CGameObject
{
protected:
	int position; // 1 or 2 or 3
public:
	CCard(float x, float y, int position) :CGameObject(x, y)
	{
		this->position = position;
		state = CARD_STATE_EMPTY;
	}

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
	int getPos() { return position; }
	void setStateFlicking(CGoal *goal);
	void setStateStatic();

};

typedef CCard* LPCARD;