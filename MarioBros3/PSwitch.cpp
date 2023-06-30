#include "PSwitch.h"
#include "debug.h"
void CPSwitch::Render()
{
	int aniId = ID_ANI_PSWITCH;
	if (state == PSWITCH_STATE_CLICKED)
	{
		aniId = ID_ANI_PSWITCH_CLICKED;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PSWITCH_BBOX_WIDTH / 2;
	t = y - PSWITCH_BBOX_HEIGHT / 2;
	r = l + PSWITCH_BBOX_WIDTH;
	b = t + PSWITCH_BBOX_HEIGHT;
}

void CPSwitch::SetState(int state)
{
	CGameObject::SetState(state);
}

void CPSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}