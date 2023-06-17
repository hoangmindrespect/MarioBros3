#include "Goal.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "Mario.h"
#include "debug.h"
#include "Animation.h"
#include "Animations.h"

void CGoal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	
	if (!isCollide)
	{
		if (isFlower)
		{
			if (GetTickCount64() - time_showing > 100)
			{
				isStar = true; isFlower = isMushroom = false;
				time_showing = GetTickCount64();
			}
		}
		else if (isStar)
		{
			if (GetTickCount64() - time_showing > 100)
			{
				isMushroom = true; isFlower = isStar = false;
				time_showing = GetTickCount64();
			}
		}
		else if (isMushroom)
		{
			if (GetTickCount64() - time_showing > 100)
			{
				isFlower = true; isStar = isMushroom = false;
				time_showing = GetTickCount64();
			}
		}
	}
	else
	{
		y -= 0.2f * dt;
	}
	
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoal::Render()
{
	if (!isCollide)
	{
		int id = ID_FLOWER;
		CSprites* s = CSprites::GetInstance();
		if (isFlower)
			id = ID_FLOWER;
		else if (isStar)
			id = ID_STAR;
		else if (isMushroom)
			id = ID_MUSHROOOM;
		s->Get(id)->Draw(x, y);
	}
	else
	{
		int id = ANI_ID_FLOWER;
		if (isFlower)
			id = ANI_ID_FLOWER;
		else if (isStar)
			id = ANI_ID_STAR;
		else if (isMushroom)
			id = ANI_ID_MUSHROOOM;
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(id)->Render(x, y);

	}
	RenderBoundingBox();
}

void CGoal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GOAL_WIDTH / 2;
	t = y - GOAL_WIDTH / 2;
	r = l + GOAL_WIDTH ;
	b = t + GOAL_WIDTH;
}