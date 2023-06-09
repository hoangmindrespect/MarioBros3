#include "PiranhaPlant.h"
#include "PlayScene.h"
void CPiranhaPlant::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (model == 1)
	{
		if (state == PIRANHA_STATE_DOWN_LEFT)
			animations->Get(ID_ANI__PIRANHA_DOWN_LEFT)->Render(x, y);
		else if (state == PIRANHA_STATE_UP_LEFT)
			animations->Get(ID_ANI__PIRANHA_UP_LEFT)->Render(x, y);
		else if (state == PIRANHA_STATE_DOWN_RIGHT)
			animations->Get(ID_ANI__PIRANHA_UP_RIGHT)->Render(x, y);
		else
			animations->Get(ID_ANI__PIRANHA_DOWN_RIGHT)->Render(x, y);
	}
	else if (model == 2)
	{
		if (state == PIRANHA_STATE_DOWN_LEFT)
			animations->Get(ID_ANI__PIRANHA_DOWN_LEFT1)->Render(x, y);
		else if(state == PIRANHA_STATE_UP_LEFT)
			animations->Get(ID_ANI__PIRANHA_UP_LEFT1)->Render(x, y);
		else if(state == PIRANHA_STATE_DOWN_RIGHT)
			animations->Get(ID_ANI__PIRANHA_UP_RIGHT1)->Render(x, y);
		else
			animations->Get(ID_ANI__PIRANHA_DOWN_RIGHT1)->Render(x, y);
	}
	else if (model == 3)
	{
		animations->Get(ID_ANI__PIRANHA_DOWN_UP)->Render(x, y);

	}
	RenderBoundingBox();
}
void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	if (model == 1 || model == 2)
	{
		if (abs((CPlayScene::player)->getx() - x) <= 131.0f)
		{
			if ((CPlayScene::player)->getx() <= x + 24.0f && (CPlayScene::player)->getx() >= x - 26.0f)
			{
				if (y != ymax + 41.0f)
				{
					goto label;
				}
			}
			else
			{
				label:
				if (IsStart_Up == false)
				{
					timeStart_Up = GetTickCount64();
					IsStart_Up = true;
				}

				if (GetTickCount64() - timeStart_Up >= 2000)
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

						KeepMoving(this);

						if (GetTickCount64() - timeStart_Fire >= 2000)
						{
							CGameObject* bul = nullptr;
							if (state == PIRANHA_STATE_DOWN_LEFT)
								bul = new CBullet(x - 4, y - 8, -0.05f, 0.02f);
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
					if (y < ymax + 41.0f)
					{
						if (!IsStart_Down)
						{
							timeStart_Down = GetTickCount64();
							IsStart_Down = true;
						}
						
						if (GetTickCount64() - timeStart_Down > 1000)
						{
							y += 0.05f * dt;
							
						}
						else
							KeepMoving(this);
						
					}
					else
					{
						y = ymax + 41.0f;
						IsStart_Down = false;
					}
				}
			}
		}
		else
		{
			y = ymax + 41.0f;
			IsStart_Fire = false;
			IsStart_Down = false;
			IsStart_Up = true;
		}
	}
	else if (model == 3)
	{
		if (abs((CPlayScene::player)->getx() - x) <= 131.0f)
		{
			if ((CPlayScene::player)->getx() <= x + 24.0f && (CPlayScene::player)->getx() >= x - 26.0f)
			{
				if (y != ymax + 33.0f)
				{
					goto label2;
				}
			}
			else
			{
				label2:
				if (IsStart_Up == false)
				{
					timeStart_Up = GetTickCount64();
					IsStart_Up = true;
				}
				if (GetTickCount64() - timeStart_Up >= 3000)
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
						if (GetTickCount64() - timeStart_Fire >= 1500)
						{
							IsStart_Fire = false;
							IsStart_Up = false;
						}

					}
				}
				else
				{
					y += 0.05f * dt;
					if (y > ymax + 33.0f)
					{
						y = ymax + 33.0f;
					}
				}
			}
		}
		else
		{
			y = ymax + 33.0f;
			IsStart_Up = true;
		}
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}
void CPiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (model == 3)
	{
		l = x - PIRANHA_BBOX_WIDTH / 2;
		t = y - PIRANHA_BBOX_BITE_HEIGHT / 2;
		r = l + PIRANHA_BBOX_WIDTH;
		b = t + PIRANHA_BBOX_BITE_HEIGHT;
	}
	else
	{
		l = x - PIRANHA_BBOX_WIDTH / 2;
		t = y - PIRANHA_BBOX_HEIGHT / 2;
		r = l + PIRANHA_BBOX_WIDTH;
		b = t + PIRANHA_BBOX_HEIGHT;
	}
}

void KeepMoving(CPiranhaPlant* a)
{
	if ((CPlayScene::player)->gety() > a->y)
		if ((CPlayScene::player)->getx() < a->x)
			a->SetState(PIRANHA_STATE_DOWN_LEFT);
		else
			a->SetState(PIRANHA_STATE_DOWN_RIGHT);
	else
		if ((CPlayScene::player)->getx() < a->x)
			a->SetState(PIRANHA_STATE_UP_LEFT);
		else
			a->SetState(PIRANHA_STATE_UP_RIGHT);
}
