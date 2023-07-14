#include "Brick.h"
#include "debug.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (model == 1)
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	else if (model == 2)
		animations->Get(ID_ANI_BRICK1)->Render(x, y);
	else if (model == 3)
		animations->Get(ID_ANI_BRICK2)->Render(x, y);
	else if (model == 4)
		animations->Get(ID_ANI_BRICK3)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (model == 2)
	{
		if (isHitBySmall)
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
					isHitBySmall = false;
				}
			}
		}
		else
		{
			IsUp = IsDown = false;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_BBOX_WIDTH / 2 - 1.0f;
	top = y - BRICK_BBOX_HEIGHT / 2;
	right = left + BRICK_BBOX_WIDTH + 1.0f;
	bottom = top + BRICK_BBOX_HEIGHT;
}

