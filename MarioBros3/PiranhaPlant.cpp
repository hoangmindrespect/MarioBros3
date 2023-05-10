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
		if (IsUp == false)
		{
			if (y >= ymax)
			{
				y -= 0.05f * dt;
			}
			else if (y < ymax)
			{
				y = ymax;
				//Sleep(3000);
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
				if (IsFire == false)
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
					IsFire = true;
				}
				IsUp = true;
			}
		}
		else if (IsUp = true)
		{
			y += 0.05f * dt;
			if (y > ymax + 47.0f)
			{
				y = ymax + 47.0f;
				IsUp = false;
				IsFire = false;
			}
		}
	}
	else
	{
		y = ymax + 47.0f;
		IsUp = false; 
		IsFire = false;
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
