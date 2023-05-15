#include "Koopas.h"
#include"ColorBox.h"
CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	nx = 1;
	this->vx = KOOPAS_WALKING_SPEED;
	SetState(KOOPAS_STATE_WALKING_RIGHT);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_DIE_DOWN)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		if (nx < 0)
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		else
			SetState(KOOPAS_STATE_WALKING_LEFT);
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if ((state == KOOPAS_STATE_DIE_DOWN) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	{
		if(nx > 0)
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		else 
			SetState(KOOPAS_STATE_WALKING_LEFT);
		y -= 8;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId = KOOPAS_STATE_WALKING_RIGHT;
	if (state == KOOPAS_STATE_WALKING_RIGHT)
		aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	else if (state == KOOPAS_STATE_WALKING_LEFT)
		aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	else if (state == KOOPAS_STATE_DIE_DOWN)
		aniId = ID_ANI_KOOPAS_DIE_DOWN;
	else if (state == KOOPAS_STATE_DIE_DOWN_SPIN)
		aniId = ID_ANI_KOOPAS_DIE_DOWN_SPIN;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE_DOWN:
		die_start = GetTickCount64();
		y += 8;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		//y -= 8;
		nx = 1;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		//y -= 8;
		nx = -1;
		break;
	case KOOPAS_STATE_DIE_DOWN_SPIN:
	{
		if (nx > 0)
			vx = KOOPAS_SPINNING_SPEED;
		else
			vx = -KOOPAS_SPINNING_SPEED;
	}
	break;

	}

}
