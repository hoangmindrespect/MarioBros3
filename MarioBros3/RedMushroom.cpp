#include "RedMushroom.h"
#include "debug.h"
CRedMushroom::CRedMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = REDMUSHROOM_GRAVITY;
	vx = 0.005f;
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
	DebugOut(L"vx: %f\n", vx * dt);
};

void CRedMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CRedMushroom*>(e->obj)) return;

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

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CRedMushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(16000)->Draw(x, y);
}

