#include "QuestionBlock.h"
#include "debug.h"
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
		if (direction == 1)
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
		}
		else if (direction == 2)
		{
			if (option == 1) // move left to right
			{
				//DebugOut(L"check xem co vo day khong");
				if (IsMoveLeft == false && x  < xmax1)
					x += 0.2f * dt;
				else
				{
					IsMoveLeft = true;
					if (IsMoveRight == false && y > xmin)
						x -= 0.2f * dt;
					else
					{
						x = xmin;
						IsMoveRight = true;
					}
				}
			}
			else if (option == 2)// move right to left
			{
				if (IsMoveRight == false && x > xmax2)
					x -= 0.2f * dt;
				else
				{
					IsMoveRight = true;
					if (IsMoveLeft == false && y < xmin)
						x += 0.2f * dt;
					else
					{
						x = xmin;
						IsMoveLeft = true;
					}
				}
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);

}