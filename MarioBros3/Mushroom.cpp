#include "Mushroom.h"
#include "debug.h"
#include "ColorBox.h"
#include "Mario.h"
#include "Platform.h"
#include "QuestionBlock.h"
CRedMushroom::CRedMushroom(float x, float y ,int k) :CGameObject(x, y)
{
	type = k;
	this->ax = 0;
	this->ay = 0;
	ymax = y - 16.0f;
	isOut = false;
	IsUp = IsDown = false;
	vx = 0;
}

void CRedMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CRedMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRedMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (dynamic_cast<CRedMushroom*>(e->obj)) return;
	
	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CRedMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (!IsUp || !IsDown)
	{
		if (IsUp == false && y > miny)
			y -= 0.2f * dt;
		else
		{
			IsUp = true;
			if (IsDown == false && y < maxy)
				y += 0.2f * dt;
			else
			{
				y = maxy;
				IsDown = true;
			}
		}
		
	}
	else
	{
		if (isOut == false)
		{
			if (y < ymax)
			{
				this->ax = 0;
				this->ay = MUSHROOM_GRAVITY;
				vx = GOOMBA_WALKING_SPEED;
				isOut = true;
			}
			else
			{
				vy = -0.01f;
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CRedMushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	if(type == 1)
		s->Get(ID_RED_MUSHROOOM)->Draw(x, y);
	else
		s->Get(ID_GREEEN_MUSHROOOM)->Draw(x, y);

	RenderBoundingBox();

}

