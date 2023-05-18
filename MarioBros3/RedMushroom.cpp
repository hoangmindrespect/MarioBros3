#include "RedMushroom.h"
#include "debug.h"
#include "ColorBox.h"
#include "Mario.h"
#include "Platform.h"
#include "QuestionBlock.h"
CRedMushroom::CRedMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = REDMUSHROOM_GRAVITY;
	vx = GOOMBA_WALKING_SPEED;
}

void CRedMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - REDMUSHROOM_BBOX_WIDTH / 2;
	top = y - REDMUSHROOM_BBOX_HEIGHT / 2;
	right = left + REDMUSHROOM_BBOX_WIDTH;
	bottom = top + REDMUSHROOM_BBOX_HEIGHT;
}

void CRedMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRedMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (dynamic_cast<CRedMushroom*>(e->obj)) return;
	else if (dynamic_cast<CMario*>(e->obj))
	{
		e->obj->sety(e->obj->gety() - 32.0f);
	}
	else if (dynamic_cast<CPlatform*>(e->obj))
	{
		CPlatform* p = dynamic_cast<CPlatform*>(e->obj);
		if (p->IsBlocking() == 0)
		{
			if (e->ny < 0)
			{
				SetYWhenCollideColorbox(p);
			}
		}
	}
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
	{
		CQuestionBlock* p = dynamic_cast<CQuestionBlock*>(e->obj);
		sety(p->gety() - 23.0f);
		vy = 0;
	}

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
void CRedMushroom::SetYWhenCollideColorbox(LPGAMEOBJECT gameobject)
{
	if (gameobject->gety() - gety() < REDMUSHROOM_BBOX_HEIGHT)
	{
		sety(gameobject->gety() - REDMUSHROOM_BBOX_HEIGHT - 1.0f);
		vy = 0;
	}
}

void CRedMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CRedMushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(16000)->Draw(x, y);

	RenderBoundingBox();

}

