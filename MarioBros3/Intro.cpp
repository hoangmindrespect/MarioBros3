#include "Intro.h"
#include "debug.h"
#include "Mushroom.h"
#include "Background.h"

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
	if (isDisplayOption)
	{
		CSprites* s = CSprites::GetInstance();

		s->Get(ID_OPTION_ONE_PLAYER)->Draw(x, y + 72.0f);
	}
	RenderBoundingBox();
}
void CIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	LPGAME game = CGame::GetInstance();

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
	if (isUp && isDown )
	{
		if (!isLugigiThrowShell)
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
					CKoopas* koo4 = new CKoopas(red->getx() + 80.0f, 10.0f, 4);
					koo4->SetState(KOOPAS_STATE_DIE_DOWN);
					koo_0 = new CKoopas(red->getx(), 10.0f, 2);
					koo_0->SetState(KOOPAS_STATE_DIE_DOWN);

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
					CPlayScene::objects.push_back(koo_0);

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
						red->SetSpeed(-0.07f, 0.07f);
						goo->SetSpeed(-0.02f, GOOMBA_GRAVITY);
					}

					if (isChangeDirection && GetTickCount64() - bracing_start > 300)
					{
						if (!test)
						{
							red->SetVx(MARIO_WALKING_SPEED);
							red->SetState(MARIO_STATE_WALKING_RIGHT);
						}
						if (!koo_0->IsDeleted() && koo_0->getx() > 268.0f)
							koo_0->Delete();
						// next -> lugigi will hold shell_koopas and kick on to the left
						if (red->getx() > 185.0f)
						{
							test = true;
							red->SetState(MARIO_STATE_IDLE);
							if (!isWaitedLugigi)
							{
								game->MakeKeyPressed(DIK_A);
								green = new CMario(278.0f, 173.0f, 2);
								green->setLevel(MARIO_LEVEL_BIG);
								green->SetState(MARIO_STATE_WALKING_LEFT);
								green->setIsHolding(true);
								koo = new CKoopas(green->getx() - 10.0f, 171.0f, 2);
								koo->SetState(KOOPAS_STATE_DIE_DOWN);
								koo->SetAy(0.0f);
								green->setKoopas(koo);
								CPlayScene::objects.insert(CPlayScene::objects.begin() + 3, koo);
								CPlayScene::objects.push_back(green);
								isWaitedLugigi = true;
							}
						}

						if (koo != NULL && green->getIsHolding())
						{
							koo->setx(green->getx() - 10.0f);
							koo->sety(171.0f);
						}

						if (green->getx() < 228.0f)
						{
							red->SetState(MARIO_STATE_WALKING_LEFT);
							if (red->getx() < 160.0f)
							{
								//red->SetState(MARIO_STATE_IDLE);
								green->setIsHolding(false);
								koo->SetState(KOOPAS_STATE_DIE_DOWN_SPIN);
								koo->SetSpeed(-0.15f, 0.1f);
								isLugigiThrowShell = true;
								green->SetState(MARIO_STATE_WALKING_RIGHT);
							}
							else
							{
								green->SetState(MARIO_STATE_IDLE);
							}
						}
					}

					// brace
					if (red->getIsOnPlatForm() && !isChangeDirection && goo->IsDeleted())
					{
						red->SetVx(-MARIO_WALKING_SPEED);
						red->Setax(MARIO_ACCEL_WALK_X);
						red->setNx(1);
						bracing_start = GetTickCount64();
						isChangeDirection = true;
					}


				}

			}
		}
		else if(!isDoneStageTwo)
		{
			if (koo->GetState() == KOOPAS_STATE_DIE_DOWN_SPIN)
			{
				if (koo->getx() < red->getx() + 50.0f)
				{
					if (red->GetState() != MARIO_STATE_JUMP)
					{
						red->SetState(MARIO_STATE_JUMP);
						red->SetVy(-0.2f);
					}
				}
			}
			else
			{
				if (red->getIsOnPlatForm())
				{
					red->SetState(MARIO_STATE_WALKING_RIGHT);
					if (red->getIsHolding())
					{
						koo->setx(red->getx() + 15.0f);
						koo->sety(171.0f);
						koo->SetAy(0.0f);
					}
					if (red->getx() > 130.0f)
					{
						isDoneStageTwo = true;
						red->SetState(MARIO_STATE_IDLE);
						red->setIsHolding(false);
						koo->SetState(KOOPAS_STATE_DIE_DOWN_SPIN);
						koo->setVx(0.15f);
					}

				}
			}

		}
		else
		{
			if (koo->getx() > 268.0f && !koochange)
			{
				koo->setx(-8.0f); 
				koochange = true;
			}
			if (red->getlevel() == MARIO_LEVEL_BIG)
			{
				red->SetLevel(MARIO_LEVEL_SMALL);
			}

			if (koo->getx() > 288.0f && !redchange)
			{
				red->SetState(MARIO_STATE_WALKING_RIGHT);
				redchange = true;
			}

			if (redchange && !redchange2)
			{
				if (red->getx() > 210.0f)
				{
					red->SetState(MARIO_STATE_WALKING_LEFT);
					redchange2 = true;
				}
			}

			if (redchange2)
			{
				if (red->getx() < 185.0f)
				{
					if (red->GetState() != MARIO_STATE_IDLE)
					{
						red->SetState(MARIO_STATE_IDLE);
						CBackground* a = new CBackground(224, 177, 16, 16, 3, 96013);
						CPlayScene::objects.push_back(a);
						time_start = GetTickCount64();
					}
					else
					{
						if (GetTickCount64() - time_start > 1000)
						{
							red->SetState(MARIO_STATE_WALKING_RIGHT);
							done = true;
						}
					}

					if (done)
						goto STAGE3;
				}
			}
		}
	}
STAGE3:
	if (red->getx() > 288.0f)
		isDisplayOption = true;
	DebugOut(L"%d\n", game->IsKeyDown(DIK_A));
	CGameObject::Update(dt, coObjects);
}
void CIntro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}