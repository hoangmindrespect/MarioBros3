#include "Intro.h"
#include "debug.h"
#include "Mushroom.h"
#include "Background.h"

bool::CIntro::isHitMario = false;
bool::CIntro::isChooseOptionOne = false;
bool::CIntro::isChooseOptionTwo = false;
bool::CIntro::isDoneStageTwo = false;
bool::CIntro::isGoombaDie = false;

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
		s->Get(ID_MAIN_SCREEN_INTRO)->Draw(x, y);
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_NUMBER_THREE)->Render(x + 5.0F, y + 25.0F);
	}
	if (!isCreateMario)
	{
		if (y < 50.0f)
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_GREEN_MARIO_WALKING_RIGHT)->Render(8.0f, GROUND_Y_INTRO);
			animations->Get(ID_ANI_MARIO_WALKING_LEFT)->Render(248.0f, GROUND_Y_INTRO);
		}
	}
	if (isChooseOptionOne || isChooseOptionTwo)
	{
		CSprites* s = CSprites::GetInstance();
		if(isChooseOptionOne)
			s->Get(ID_OPTION_ONE_PLAYER)->Draw(x, y + 72.0f);
		else if(isChooseOptionTwo)
			s->Get(ID_OPTION_TWO_PLAYER)->Draw(x, y + 72.0f);

	}
	RenderBoundingBox();
}
void CIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	LPGAME game = CGame::GetInstance();

	////////////////		STAGE 1: OPEN THE CURTAIN AND DROP DOWN THE TITLE [MARIO BROS 3]		//////////////////////
	float mario_x = 0.0f, mario_y = 0.0f, lugigi_x = 0.0f, lugigi_y = 0.0f;
	if (!isChooseOptionOne && !isChooseOptionTwo)
	{
		if (red != NULL)
		{
			red->GetPosition(mario_x, mario_y);
		}

		if (green != NULL)
		{
			green->GetPosition(lugigi_x, lugigi_y);
		}
	}

	/*STEP 1*/
	if(y > TOP_EDGE_LIMIT && !isUp)
	{
		y -= VELOCITY_OPEN_CURTAIN * dt;

		//curtain open a half -> mario and lugigi appear
		if (y < COORDINATE_TO_CREATE_LU_MA)
		{
			if (!isCreateMario)
			{
				//delay before lugigi and mario moving
				if (GetTickCount64() - time_start > 2030)
				{
					//1.1: CREATE LUGIGI AT THE LEFT BACK AND MOVE
					green = new CMario(8.0f, GROUND_Y_INTRO, 2);
					green->setLevel(MARIO_LEVEL_BIG);
					green->SetState(MARIO_STATE_WALKING_RIGHT);

					//1.2: CREATE MARIO AT THE RIGHT BACK AND MOVE
					red = new CMario(248.0f, GROUND_Y_INTRO, 1);
					red->setLevel(MARIO_LEVEL_BIG);
					red->SetState(MARIO_STATE_WALKING_LEFT);

					CPlayScene::objects.push_back(red);
					CPlayScene::objects.push_back(green);
					isCreateMario = true;
				}
			}

		}
	}
	/*STEP 2*/
	else if(y < BOTTOM_EDGE_LIMIT && !isDown)
	{
		isUp = true;
		if (lugigi_x > COORDINATE_X_LUGIGI_JUMP)
		{
			//2.1: LUGIGI JUMPING TO HIT MARIO
			if (!isHitMario)
			{
				green->SetState(MARIO_STATE_JUMP);
			}
			else //2.2: LUGIGI FALL ONTO MARIO AND DROP TITLE
			{
				if (green->gety() > TOP_EDGE_LIMIT_LUGIGI && !isFallOntoMario)
				{
					green->SetSpeed(MARIO_WALKING_SPEED - 0.03f, -0.2f);
				}
				else
				{
					if (!isFallOntoMario)
					{
						red->setIsSitting(false);
						red->sety(red->gety() - (MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITTING_BBOX_HEIGHT) / 2);
						isFallOntoMario = true;
					}
					//ensure lugigi collide with bottom edge and change direction
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
		//ensure main screen has true position
		y = BOTTOM_EDGE_LIMIT;
	}

	// shaking the title when drop it down
	if (isUp && isDown && !isShaked)
	{
		if (GetTickCount64() - time_start <= 1000)
		{
			if (!flag)
			{
				y -= 1.0f; flag = true;
			}
			else
			{
				y += 1.0f; flag = false;
			}

		}
		else
			isShaked = true;
	}

	////////////////		STAGE 2: CREATE AND HANDLE OBJECT		//////////////////////
	if (isShaked && !isDoneStageTwo)
	{
		if (!isLugigiThrowShell)
		{
			/*STEP 1: CREATE OBJECT*/
			if (!isCreateObject)
			{
				//black shell
				CKoopas* black_shell = new CKoopas(mario_x + 60.0f, TOP_EDGE_LIMIT_LUGIGI, 4);
				black_shell->SetState(KOOPAS_STATE_DIE_DOWN);

				// koopas - which fall onto mario
				first_koopas = new CKoopas(mario_x, TOP_EDGE_LIMIT_LUGIGI, 2);
				first_koopas->SetState(KOOPAS_STATE_DIE_DOWN);

				//goomba
				goo = new CGoomba(mario_x - 50.0f, 1);
				goo->SetSpeed(0.0f, KOOPAS_GRAVITY);

				//leaf
				leaf = new CLeaf(mario_x, 10.0f);

				//Mushroom -> lazy to redefine -> I set it from here
				CRedMushroom* mus = new CRedMushroom(mario_x - 50.0f, TOP_EDGE_LIMIT_LUGIGI, 1);
				mus->setnx(-1);
				mus->setIsUp(true);
				mus->setIsDown(true);
				mus->setIsOut(true);
				mus->setAy(0.0005f);
				mus->setVx(-0.03f);

				CPlayScene::objects.push_back(goo);
				CPlayScene::objects.push_back(leaf);
				CPlayScene::objects.push_back(mus);
				CPlayScene::objects.push_back(black_shell);
				CPlayScene::objects.push_back(first_koopas);

			}
			isCreateObject = true;

			/*STEP 2: MARIO GET LEAF AND UP LEVEL = TAIL*/
			if (red->getlevel() == MARIO_LEVEL_TAIL)
				isGotLeaf = true;

			if (!isGotLeaf)
			{
				if (leaf->gety() > 70.0f)
				{
					if (red->getlevel() != MARIO_LEVEL_TAIL) {
						red->SetState(MARIO_STATE_JUMP);
					}
				}
			}
			/*STEP 3: MARIO IS FLYING*/
			else
			{
				//3.1: MAKE GOOMBA MOVING AND HIT GOOMBA
				if (goo->GetState() != GOOMBA_STATE_DIE)
				{
					red->SetIsRelease(true);
					red->SetSpeed(-0.07f, 0.07f);
					goo->SetSpeed(-0.02f, GOOMBA_GRAVITY);
				}

				//3.3 BRACING TO CHANGE DIRECTION
				if (isChangeDirection)
				{
					//3.3.1 Mario will moving and kick first koopas -> first koopas hit black shell
					if (GetTickCount64() - bracing_start > 300)
					{
						if (!isFaceToFaceLugigi)
						{
							red->SetVx(MARIO_WALKING_SPEED);
							red->SetState(MARIO_STATE_WALKING_RIGHT);
						}
					}

					if (!first_koopas->IsDeleted() && !isDeleteFirstKoopas)
					{
						if (first_koopas->getx() > 248.0f)
						{
							first_koopas->Delete();
							isDeleteFirstKoopas = true;
						}
					}

					// 3.3.2 Mario stop and waiting Lugigi hodling shell come out
					if (mario_x > 185.0f)
					{
						isFaceToFaceLugigi = true;
						red->SetState(MARIO_STATE_IDLE);
						red->SetVx(0.0f);
						if (!isWaitedLugigi && isDeleteFirstKoopas)
						{
							game->MakeKeyPressed(DIK_A);

							//reset coordinate and state of lugigi
							green = new CMario(298.0f, GROUND_Y_INTRO, 2);
							green->setLevel(MARIO_LEVEL_BIG);
							green->SetState(MARIO_STATE_WALKING_LEFT);
							green->setIsHolding(true);

							//define second koopas is hold by lugigi
							//ensure first not collide with second
							second_koopas = new CKoopas(298.0f, GROUND_Y_INTRO - 2.0f, 2);
							second_koopas->SetState(KOOPAS_STATE_DIE_DOWN);
							second_koopas->SetAy(0.0f);

							//ensure second koopas is drawn before Mario
							CPlayScene::objects.insert(CPlayScene::objects.begin() + 3, second_koopas);
							CPlayScene::objects.push_back(green);
							isWaitedLugigi = true;
						}
					}
					
					//if(second_koopas != NULL)
					//	DebugOut(L"%f, %f\n", second_koopas->getx(), second_koopas->gety());

					//update position second koopas arcoding Lugigi
					if (green->getIsHolding())
					{
						if(lugigi_x < 500.0f) // ensure second koopas fall out platform
							second_koopas->SetPosition(lugigi_x - 12.0f, GROUND_Y_INTRO - 2.0f);
					}

					//3.3.3 Lugigi stop at this position and Kick second koopas
					if (green->getx() < 228.0f)
					{

						red->SetState(MARIO_STATE_WALKING_LEFT);
						//when red get right positon -> lugigi kick 
						if (red->getx() < 160.0f)
						{
							second_koopas->SetState(KOOPAS_STATE_DIE_DOWN_SPIN);
							second_koopas->SetSpeed(-0.15f, 0.1f);

							green->setIsHolding(false);
							green->SetState(MARIO_STATE_WALKING_RIGHT);

							isLugigiThrowShell = true;
						}
						else
						{
							green->SetState(MARIO_STATE_IDLE);
						}
					}
				}

				//3.2: MAKE MARIO BRACING AFTER HIT GOOMBA
				if (!isChangeDirection && isGoombaDie)
				{
					red->SetState(MARIO_STATE_WALKING_RIGHT);
					red->SetIsRelease(false);
					bracing_start = GetTickCount64();
					isChangeDirection = true;
				}
			}
		}
		/*STEP 3: MARIO HIT SECOND KOOPAS AND HOLD IT TO ATTACK LUGIGI*/
		else if(!isMarioHitKoopas)
		{
			//3.1: JUMP TO HIT
			if (second_koopas->GetState() == KOOPAS_STATE_DIE_DOWN_SPIN)
			{
				if (second_koopas->getx() < red->getx() + 50.0f)
				{
					if (red->GetState() != MARIO_STATE_JUMP)
					{
						red->SetState(MARIO_STATE_JUMP);
						red->SetVy(-0.2f);
					}
				}
			}
			//3.2: HOLDING AND KICK SHELL TO ATTACK LUGIGI
			else
			{
				if (red->getIsOnPlatForm())
				{
					red->SetState(MARIO_STATE_WALKING_RIGHT);
					if (red->getIsHolding())
					{
						second_koopas->SetPosition(mario_x + 15.0f, GROUND_Y_INTRO - 2.0f);
						second_koopas->SetAy(0.0f);
					}
					if (mario_x > 130.0f)
					{
						isMarioHitKoopas = true;
						red->SetState(MARIO_STATE_IDLE);
						red->setIsHolding(false);
						second_koopas->SetState(KOOPAS_STATE_DIE_DOWN_SPIN);
						second_koopas->setVx(0.15f);
					}

				}
			}

		}
		/*STEP 4:*/
		else
		{
			//4.1: MAKE SHELL START FROM LEFT EDGE WHEN IT OUT OF RIGHT EDGE
			if (second_koopas->getx() > 268.0f && !isKoopasChangedDirection)
			{
				second_koopas->setx(-8.0f);
				isKoopasChangedDirection = true;
			}

			if (red->getlevel() == MARIO_LEVEL_BIG)
				red->SetLevel(MARIO_LEVEL_SMALL);

			//4.2: CHANGE DIRECTION
			if (second_koopas->getx() > 288.0f && !isSmallChangedDirectFirst)
			{
				red->SetState(MARIO_STATE_WALKING_RIGHT);
				isSmallChangedDirectFirst = true;
			}

			//4.3: CHANGE DIRECTION
			if (isSmallChangedDirectFirst && !isSmallChangedDirectSecond)
			{
				if (red->getx() > 215.0f)
				{
					red->SetState(MARIO_STATE_WALKING_LEFT);
					isSmallChangedDirectSecond = true;
				}
			}

			//4.4: CHANGE DIRECTION AND DONE STAGE 2
			if (isSmallChangedDirectSecond)
			{
				if (mario_x < 185.0f)
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
						if (GetTickCount64() - time_start > 500)
						{
							red->SetState(MARIO_STATE_WALKING_RIGHT);
							isDoneStageTwo = true;
						}
					}
				}
			}
		}
	}
	////////////////		STAGE 3: HANDLE 3 KOOPAS MOVING	AND DISPLAY OPTION	//////////////////////

	if (isDoneStageTwo)
	{
		game->MakeKeyUp(DIK_A);

		if (mario_x > 288.0f)
		{
			red->Delete();
			green->Delete();
			if (!isChooseOptionOne && !isChooseOptionTwo)
			{
				isChooseOptionOne = true;
				koopas_number_one = new CKoopas(8.0f, GROUND_Y_INTRO, 2);
				koopas_number_one->SetState(KOOPAS_STATE_WALKING_RIGHT);

				CKoopas* koopas_number_two = new CKoopas(-48.0f, GROUND_Y_INTRO, 2);
				koopas_number_two->SetState(KOOPAS_STATE_WALKING_RIGHT);

				CKoopas* koopas_number_three = new CKoopas(-104.0f, GROUND_Y_INTRO, 2);
				koopas_number_three->SetState(KOOPAS_STATE_WALKING_RIGHT);

				CPlayScene::objects.push_back(koopas_number_one);
				CPlayScene::objects.push_back(koopas_number_two);
				CPlayScene::objects.push_back(koopas_number_three);
			}
		}
		if (!isCreateFastKoopas)
		{
			if (koopas_number_one != NULL && koopas_number_one->getx() > 258.0f)
			{
				CKoopas* koopas_number_four = new CKoopas(-104.0f, GROUND_Y_INTRO, 2);
				koopas_number_four->SetState(KOOPAS_STATE_WALKING_RIGHT);
				koopas_number_four->setVx(KOOPAS_WALKING_SPEED * 3);
				isCreateFastKoopas = true;
				CPlayScene::objects.push_back(koopas_number_four);

			}
		}
	}
	CGameObject::Update(dt, coObjects);
}
void CIntro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}