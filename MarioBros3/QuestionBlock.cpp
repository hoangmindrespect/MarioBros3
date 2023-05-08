#include "QuestionBlock.h"

void CQuestionBlock::Render()
{
	int aniId = ID_ANI_QUESTIONBLOCK;
	if (state == QUESTIONBLOCK_STATE_EMPTY)
	{
		aniId = ID_ANI_QUESTIONBLOCK_EMPTY;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
	t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBLOCK_BBOX_WIDTH;
	b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::SetState(int state)
{
	CGameObject::SetState(QUESTIONBLOCK_STATE_EMPTY);
}

void CQuestionBlock::Update(DWORD dt ,vector<LPGAMEOBJECT>* coObjects = NULL)
{
	if (state == QUESTIONBLOCK_STATE_EMPTY)
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
		if (type != 1)
			return;
		else if (obj != nullptr)
		{
			if (IsUpObj == false && obj->gety() > minyo)
			{
				yo -= 0.2f * dt;
				obj->sety(yo);
			}
			else
			{
				IsUpObj = true;
				if (IsDownObj == false && yo < maxyo)
				{
					yo += 0.2f * dt;
					obj->sety(yo);
				}
				else
				{
					obj->sety(maxyo);
					obj->sety(99999);
					obj = nullptr;
					IsDownObj = true;
				}
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);

}