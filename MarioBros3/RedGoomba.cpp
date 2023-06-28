#include "RedGoomba.h"
#include "Platform.h"
#include "debug.h"
#include "Goomba.h"
CRedGoomba::CRedGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	nx = -1;
	this->ay = GOOMBA_GRAVITY;
	vx = -RED_GOOMBA_WALKING_SPPED;
	die_start = -1;
	SetState(RED_GOOMBA_STATE_WALKING_WITH_WINGS);
	isNotJump = true;
	isJump = false;
	isPrepare = false;
	time_For_Action = GetTickCount64();
	countPre = 0;
}

void CRedGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == RED_GOOMBA_STATE_DIE)
	{
		left = x - RED_GOOMBA_BBOX_WIDTH / 2;
		top = y - RED_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + RED_GOOMBA_BBOX_WIDTH;
		bottom = top + RED_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == RED_GOOMBA_STATE_WALKING_NONE_WINGS)
	{
		left = x - RED_GOOMBA_BBOX_WIDTH / 2;
		top = y - RED_GOOMBA_BBOX_HEIGHT / 2;
		right = left + RED_GOOMBA_BBOX_WIDTH;
		bottom = top + RED_GOOMBA_BBOX_HEIGHT;
	}
	else
	{
		left = x - RED_GOOMBA_WINGS_BBOX_WIDTH / 2;
		top = y - RED_GOOMBA_WINGS_BBOX_HEIGHT / 2;
		right = left + RED_GOOMBA_WINGS_BBOX_WIDTH;
		bottom = top + RED_GOOMBA_WINGS_BBOX_HEIGHT;
	}
}

void CRedGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRedGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	else if (dynamic_cast<CRedGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

}

void CRedGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == RED_GOOMBA_STATE_DIE || state == RED_GOOMBA_STATE_DIE_BY_KOOPAS) && (GetTickCount64() - die_start > 500))
	{
		isDeleted = true;
		return;
	}

	if (state != RED_GOOMBA_STATE_WALKING_NONE_WINGS && state != RED_GOOMBA_STATE_DIE && state != RED_GOOMBA_STATE_DIE_BY_KOOPAS)
	{
		if (isNotJump)
		{
			if (GetTickCount64() - time_For_Action > 1000)
			{
				isNotJump = false;
				isPrepare = true;
				isJump = false;
				SetState(RED_GOOMBA_STATE_PREPARING_WITH_WINGS);
				time_For_Action = GetTickCount64();
			}
		}
		else if (isPrepare)
		{
			if (GetTickCount64() - time_For_Action > 200)
			{
				if (countPre > 3)
				{
					countPre = 0;
					isNotJump = false;
					isPrepare = false;
					isJump = true;
					SetState(RED_GOOMBA_STATE_JUMPING_WITH_WINGS);
					time_For_Action = GetTickCount64();
				}
				else
				{
					countPre++;
					SetState(RED_GOOMBA_STATE_PREPARING_WITH_WINGS);
					time_For_Action = GetTickCount64();
				}
			}
		}
		else if (isJump)
		{
			if (GetTickCount64() - time_For_Action > 500)
			{
				isNotJump = true;
				isPrepare = false;
				isJump = false;
				SetState(RED_GOOMBA_STATE_WALKING_WITH_WINGS);
				time_For_Action = GetTickCount64();
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CRedGoomba::Render()
{
	int aniId = ID_RED_GOOMBA_WALKING_NOT_JUMP;
	if (state == RED_GOOMBA_STATE_JUMPING_WITH_WINGS || state == RED_GOOMBA_STATE_PREPARING_WITH_WINGS)
	{
		aniId = ID_RED_GOOMBA_WALKING_JUMP;
	}
	else if (state == RED_GOOMBA_STATE_WALKING_WITH_WINGS)
		aniId = ID_RED_GOOMBA_WALKING_NOT_JUMP;
	else if (state == RED_GOOMBA_STATE_WALKING_NONE_WINGS)
		aniId = ID_RED_GOOMBA_WALKING;
	else if (state == RED_GOOMBA_STATE_DIE)
		aniId = ID_RED_GOOMBA_DIE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CRedGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case RED_GOOMBA_STATE_WALKING_WITH_WINGS:
		{
			vy = 0;
			ax = 0;
			ay = RED_GOOMBA_GRAVITY;
			break;
		}
		case RED_GOOMBA_STATE_PREPARING_WITH_WINGS:
		{
			vy = -0.07f;
			ay = RED_GOOMBA_GRAVITY;
			ax = 0;
			break;
		}
		case RED_GOOMBA_STATE_JUMPING_WITH_WINGS:
		{
			vy = -0.23f;
			ay = RED_GOOMBA_GRAVITY;
			ax = 0;
			break;
		}
		case RED_GOOMBA_STATE_WALKING_NONE_WINGS:
		{
			ax = 0;
			vy = 0.0f;
			ay = RED_GOOMBA_GRAVITY;
			break;
		}
		case RED_GOOMBA_STATE_DIE:
		{
			vx = vy = ax = ay = 0;
			die_start = GetTickCount64();
			break;
		}
		case RED_GOOMBA_STATE_DIE_BY_KOOPAS:
		{
			die_start = GetTickCount64();
			vx = 0.03f;;
			vy = -0.3f;
			break;
		}
	}
}
