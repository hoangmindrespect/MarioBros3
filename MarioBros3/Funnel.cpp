#include "Funnel.h"
#include "debug.h"
#include "PlayScene.h"
void CFunnel::Render()
{
	RenderBoundingBox();
}

void CFunnel::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FUNNEL_BBOX_WIDTH / 2;
	t = y - FUNNEL_BBOX_HEIGHT / 2;
	r = l + FUNNEL_BBOX_WIDTH;
	b = t + FUNNEL_BBOX_HEIGHT;
}

void CFunnel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}