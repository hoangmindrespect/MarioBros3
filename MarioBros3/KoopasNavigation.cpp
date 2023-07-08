#include "KoopasNavigation.h"
#include "debug.h"
#include "ColorBox.h"
#include "Platform.h"
#include "Mario.h"
void CKoopasNavigation::Render()
{
	RenderBoundingBox();
}

void CKoopasNavigation::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - KOOPAS_NAVIGATION_WIDTH / 2;
	t = y - KOOPAS_NAVIGATION_WIDTH / 2;
	r = l + KOOPAS_NAVIGATION_WIDTH;
	b = t + KOOPAS_NAVIGATION_WIDTH;
}

void CKoopasNavigation::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopasNavigation::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
		return;
}

void CKoopasNavigation::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	if (koopas == NULL)
	{
		this->Delete();
		return;
	}

	vx = koopas->getVx();
	vy += ay * dt;
	if (this->y - koopas->gety() > KOOPAS_NAVIGATION_WIDTH / 2)
		ChangeDirection();
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopasNavigation::ChangeDirection()
{
	if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT)
		koopas->SetState(KOOPAS_STATE_WALKING_RIGHT);
	else if(koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
		koopas->SetState(KOOPAS_STATE_WALKING_LEFT);

	float koopas_x = 0.0f, koopas_y = 0.0f;
	int HostDirection = koopas->getnx();
	koopas->GetPosition(koopas_x, koopas_y);

	if (HostDirection > 0)
	{
		x = koopas_x + KOOPAS_NAVIGATION_WIDTH + 2.0f;
		y = koopas_y;
	}
	else
	{
		x = koopas_x - KOOPAS_NAVIGATION_WIDTH - 2.0f;
		y = koopas_y;
	}
}
