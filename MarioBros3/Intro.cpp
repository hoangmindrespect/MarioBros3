#include "Intro.h"
#include "debug.h"

bool::CIntro::isHitRed = false;
void CIntro::Render()
{
	if (!isUp)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_OPEN_CURTAIN)->Draw(x, y);
	}
	else 
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_DROP_TITLE_GAME)->Draw(x, y);
	}
	
	if (isCreateObject)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(166039)->Draw(x, y);
		//s->Get(ID_OPTION_ONE_PLAYER)->Draw(x, y + 72.0f);
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_NUMBER_THREE)->Render(x + 5.0F, y + 25.0F);
	}
	if (!isCreateMario)
	{
		if (y < 50.0f)
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_GREEN_MARIO_WALKING_RIGHT)->Render(8.0f, 173.0f);
			animations->Get(ID_ANI_MARIO_WALKING_LEFT)->Render(248.0f, 173.0f);

		}
	}
	RenderBoundingBox();
}
void CIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	
	//control open the curtain and drop title MARIO BROS 3
	if(y > TOP_EDGE_LIMIT && !isUp)
	{
		y -= VELOCITY_OPEN_CURTAIN * dt;
		if (y < 50.0F)
		{
			if (!isCreateMario)
			{
				if (GetTickCount64() - time_start > 2000)
				{
					green = new CMario(8.0f, 173.0f, 2);
					green->setLevel(MARIO_LEVEL_BIG);
					green->SetState(MARIO_STATE_WALKING_RIGHT);

					red = new CMario(248.0f, 173.0f, 1);
					red->setLevel(MARIO_LEVEL_BIG);
					red->SetState(MARIO_STATE_WALKING_LEFT);

					CPlayScene::objects.push_back(red);
					CPlayScene::objects.push_back(green);
					isCreateMario = true;
				}
		}

		}
	}
	else if(y < BOTTOM_EDGE_LIMIT && !isDown)
	{
		isUp = true;
		if (green->getx() > 5.0f)
		{
			if (!isHitRed)
			{
				green->SetState(MARIO_STATE_JUMP);
			}
			else
			{
				if (green->gety() > 10.0f && !isFallDown)
				{
					green->SetVy(-0.2f);
					green->SetVx(0.03f);
				}
				else
				{
					if (!isFallDown)
					{
						red->setIsSitting(false);
						red->SetVy(0.0f);
						red->sety(red->gety() - 10.0f);
						isFallDown = true;
					}
					green->SetVy(VELOCITY_DROP_TITLE_GAME);
					green->setx(green->getx() + 0.05f * dt);
					y += VELOCITY_DROP_TITLE_GAME * dt;
				}
			}
		}
	}
	else
	{
		if(!isDown)
			time_start = GetTickCount64();
		isDown = true;
		y = BOTTOM_EDGE_LIMIT;
	}

	// shaking the title when drop it down
	if (isUp && isDown)
	{
		if (GetTickCount64() - time_start <= 1000)
		{
			if (!flag)
			{
				y -= 1; flag = true;
			}
			else
			{
				y += 1; flag = false;
			}

		}
		else // main menu with objects: mushroom, goomba,green defend koopas, star, black defend koopas fall down
		{
			/*if (!isCreateObject)
			{
				CMario* ma = new CMario(50, 80);
				CGoomba* go = new CGoomba(60, 120);
				CPlayScene::objects.push_back(ma);
				CPlayScene::objects.push_back(go);
			}*/
			isCreateObject = true;
		}
	}
	CGameObject::Update(dt, coObjects);
}
void CIntro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}