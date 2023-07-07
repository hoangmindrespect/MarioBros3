#include "KoopasNavigation.h"
#include "debug.h"
#include "ColorBox.h"
#include "Platform.h"
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

}

void CKoopasNavigation::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CKoopasNavigation::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	
	if (koopas != NULL)
	{
		float koopas_x = 0.0f, koopas_y = 0.0f;
		int HostDirection = koopas->getnx();
		koopas->GetPosition(koopas_x, koopas_y);

		if (HostDirection > 0)
		{
			x = koopas_x + KOOPAS_NAVIGATION_WIDTH + 4.0f;
			y = koopas_y + 6.0f;
		}
		else
		{
			x = koopas_x - KOOPAS_NAVIGATION_WIDTH - 4.0f;
			y = koopas_y + 6.0f;
		}
	}
	else if (koopas == NULL)
		this->Delete();
}