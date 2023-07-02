#include "Intro.h"
#include "debug.h"
#include "Mushroom.h"

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
					if (!isFallDown) // cần xử lý lại chỗ này nha bạn ơi 
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
			if (!isCreateObject)
			{
				CKoopas* koo4 = new CKoopas(red->getx() + 50.0f, 10.0f, 4);
				koo4->SetState(KOOPAS_STATE_DIE_DOWN);
				CKoopas* koo2 = new CKoopas(red->getx() + 5.0f, 10.0f, 2);
				koo2->SetState(KOOPAS_STATE_DIE_DOWN);

				goo = new CGoomba(red->getx() - 50.0f, 1);
				goo->SetSpeed(0.0f, KOOPAS_GRAVITY);
				leaf = new CLeaf(red->getx(), 10.0f);
				CRedMushroom* mus = new CRedMushroom(red->getx() - 50.0f, 10.0f, 1);
				mus->setnx(-1);
				mus->setIsUp(true);
				mus->setIsDown(true);
				mus->setIsOut(true);
				mus->setAy(0.0005f);
				mus->setVx(-0.03f);
				CPlayScene::objects.push_back(goo);
				CPlayScene::objects.push_back(leaf);
				CPlayScene::objects.push_back(mus);
				CPlayScene::objects.push_back(koo4);	
				CPlayScene::objects.push_back(koo2);

			}
			isCreateObject = true;
			if (!leaf->IsDeleted())
			{
				if (leaf->gety() > 70.0f)
				{
					if (red->getlevel() != MARIO_LEVEL_TAIL) {
						red->SetState(MARIO_STATE_JUMP);
					}
				}
			}
			else
			{
				if (goo->GetState() != GOOMBA_STATE_DIE)
				{
					red->SetIsRelease(true);
					red->SetSpeed(-0.06f, 0.07f);
					goo->SetSpeed(-0.02f, GOOMBA_GRAVITY);
				}

				if (isChangeDirection)
				{
					red->SetVx(MARIO_WALKING_SPEED);
					red->SetState(MARIO_STATE_WALKING_RIGHT);
				}

				if (red->getIsOnPlatForm() && !isChangeDirection && goo->IsDeleted())
				{
					red->SetVx(-MARIO_WALKING_SPEED);
					red->Setax(MARIO_ACCEL_WALK_X);
					red->setNx(1);
					isChangeDirection = true;
				}
				

			}

		}
	}
	CGameObject::Update(dt, coObjects);
}
void CIntro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}