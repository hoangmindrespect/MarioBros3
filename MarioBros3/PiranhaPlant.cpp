#include "PiranhaPlant.h"
#include "PlayScene.h"
void CPiranhaPlant::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == PIRANHA_STATE_DOWN_LEFT)
		animations->Get(ID_ANI__PIRANHA_DOWN_LEFT)->Render(x, y);
	else if(state == PIRANHA_STATE_UP_LEFT)
		animations->Get(ID_ANI__PIRANHA_UP_LEFT)->Render(x, y);
	else if(state == PIRANHA_STATE_DOWN_RIGHT)
		animations->Get(ID_ANI__PIRANHA_UP_RIGHT)->Render(x, y);
	else
		animations->Get(ID_ANI__PIRANHA_DOWN_RIGHT)->Render(x, y);

	RenderBoundingBox();
}
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	if (abs((CPlayScene::player)->getx() - x) <= 200.0f)
	{
		if (IsStart_Up == false)
		{
			timeStart_Up = GetTickCount64();
			IsStart_Up = true;
		}
		ULONGLONG now1 = GetTickCount64();
		if (now1 - timeStart_Up >= 2000)
		{
			if (y >= ymax)
			{
				y -= 0.05f * dt;
			}
			else if (y < ymax)
			{
				if (IsStart_Fire == false)
				{
					timeStart_Fire = GetTickCount64();
					IsStart_Fire = true;
				}
				
				if ((CPlayScene::player)->gety() > y)
					if ((CPlayScene::player)->getx() < x)
						state = PIRANHA_STATE_DOWN_LEFT;
					else
						state = PIRANHA_STATE_DOWN_RIGHT;
				else
					if ((CPlayScene::player)->getx() < x)
						state = PIRANHA_STATE_UP_LEFT;
					else
						state = PIRANHA_STATE_UP_RIGHT;
				ULONGLONG now = GetTickCount64();
				if (now - timeStart_Fire >= 1500)
				{
					CGameObject* bul = nullptr;
					if (state == PIRANHA_STATE_DOWN_LEFT)
						bul = new CBullet(x -4, y - 8, -0.05f, 0.02f);
					else if (state == PIRANHA_STATE_UP_LEFT)
						bul = new CBullet(x - 4, y - 8, -0.05f, -0.02f);
					else if (state == PIRANHA_STATE_DOWN_RIGHT)
						bul = new CBullet(x + 4, y - 8, 0.05f, 0.02f);
					else
						bul = new CBullet(x + 4, y - 8, 0.05f, -0.02f);
					CPlayScene::objects.push_back(bul);
					IsStart_Fire = false;
					IsStart_Up = false;
				}
				
			}
		}
		else 
		{
			y += 0.05f * dt;
			if (y > ymax + 47.0f)
			{
				y = ymax + 47.0f;
			}
		}
	}
	else
	{
		y = ymax + 47.0f;
		IsStart_Fire = false;
		IsStart_Up = true;
	}
	
	//DebugOut(L"ma: %f, pi: %f\n", (CPlayScene::player)->getx(), x);
	CGameObject::Update(dt, coObjects);
}
void CPiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_BBOX_WIDTH / 2;
	t = y - PIRANHA_BBOX_HEIGHT / 2;
	r = l + PIRANHA_BBOX_WIDTH;
	b = t + PIRANHA_BBOX_HEIGHT;
}
