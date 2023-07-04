#include "SampleKeyEventHandler.h"
#include "debug.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
#include "MarioStop.h"
#include "Intro.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	if (CPlayScene::IsIntroScene())
	{
		if (CIntro::isDoneStageTwo)
		{
			if (KeyCode == DIK_S)
			{
				if (CIntro::isChooseOptionOne)
				{
					CIntro::isChooseOptionOne = false;
					CIntro::isChooseOptionTwo = true;
				}
				else
				{
					CIntro::isChooseOptionOne = true;
					CIntro::isChooseOptionTwo = false;
				}
			}
			else if (KeyCode == DIK_W)
			{
				CGame::GetInstance()->InitiateSwitchScene(1);
			}
		}
	}
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	if (!mario)
		return;
	switch (KeyCode)
	{
	case DIK_DOWN:
	{
		if (mario->getIsInMap() == 0)
			mario->SetState(MARIO_STATE_SIT);
		else
		{
			for (int i = 0; i < CPlayScene::stop.size(); i++)
			{
				if (mario->getx() == CPlayScene::stop[i]->getx() && mario->gety() == CPlayScene::stop[i]->gety())
				{
					CMarioStop* a = dynamic_cast<CMarioStop*>(CPlayScene::stop[i]);
					if (a->getCanMoveDown() == 0)
						mario->SetIsMoveDown(false);
					else
					{
						if (mario->getIsMoveLeft() || mario->getIsMoveUp() || mario->getIsMoveRight())
							break;
						else
							mario->SetIsMoveDown(true);
					}
					break;
				}
			}
		
		}
		break;
	}
	case DIK_RIGHT:
	{
		if (mario->getIsInMap() == 1)
		{
			for (int i = 0; i < CPlayScene::stop.size(); i++)
			{
				if (mario->getx() == CPlayScene::stop[i]->getx() && mario->gety() == CPlayScene::stop[i]->gety())
				{
					
					CMarioStop* a = dynamic_cast<CMarioStop*>(CPlayScene::stop[i]);
					if (a->getCanMoveRight() == 0)
					{
						mario->SetIsMoveRight(false);
					}
					else
					{
						if (mario->getIsMoveLeft() || mario->getIsMoveUp() || mario->getIsMoveDown())
							break;
						else
							mario->SetIsMoveRight(true);
					}
					break;
					
				}
			}
			
		}
		break;
	}
	case DIK_UP:
	{
		if (mario->getIsInMap() == 1)
		{
			for (int i = 0; i < CPlayScene::stop.size(); i++)
			{
				if (mario->getx() == CPlayScene::stop[i]->getx() && mario->gety() == CPlayScene::stop[i]->gety())
				{
					CMarioStop* a = dynamic_cast<CMarioStop*>(CPlayScene::stop[i]);					
					if (a->getCanMoveUp() == 0)
						mario->SetIsMoveUp(false);
					else
					{
						
						if (mario->getIsMoveLeft() || mario->getIsMoveRight() || mario->getIsMoveDown())
							break;
						else
							mario->SetIsMoveUp(true);
					}
					break;
				}
				
			}
			
		}
		break;
	}case DIK_LEFT:
	{
		if (mario->getIsInMap() == 1)
		{
			for (int i = 0; i < CPlayScene::stop.size(); i++)
			{
				if (mario->getx() == CPlayScene::stop[i]->getx() && mario->gety() == CPlayScene::stop[i]->gety())
				{
					CMarioStop* a = dynamic_cast<CMarioStop*>(CPlayScene::stop[i]);
					if (a->getCanMoveLeft() == 0)
						mario->SetIsMoveLeft(false);
					else
					{
						if (mario->getIsMoveRight() || mario->getIsMoveUp() || mario->getIsMoveDown())
							break;
						else
							mario->SetIsMoveLeft(true);
					}
					break;
				}
			}
			
		}
		break;
	}
	case DIK_S:
	{	
		if (mario->getIsInMap() == 1)
		{
			for (int i = 0; i < CPlayScene::stop.size(); i++)
			{
				if (mario->getx() == CPlayScene::stop[i]->getx() && mario->gety() == CPlayScene::stop[i]->gety())
				{
					CMarioStop* a = dynamic_cast<CMarioStop*>(CPlayScene::stop[i]);
					if (a->getType() == 1)
					{
						CGame::GetInstance()->InitiateSwitchScene(a->getIDScene());
					}
					break;
				}
			}
		}
		else
			mario->SetState(MARIO_STATE_JUMP);
		break;
	}
	case DIK_1:
	{
		if (mario->getIsInMap() == false)
		{
			mario->SetLevel(MARIO_LEVEL_SMALL);
			break;
		}
	}
	case DIK_2:
	{
		if (mario->getIsInMap() == false)
		{
			mario->SetLevel(MARIO_LEVEL_BIG);
			break;
		}
	}
	case DIK_3:
	{	
		if (mario->getIsInMap() == false)
		{
			mario->SetLevel(MARIO_LEVEL_TAIL);
			break;
		}
	}
	case DIK_0:
	{
		if (mario->getIsInMap() == false)
		{
			mario->SetState(MARIO_STATE_DIE);
			break;
		}
	}
	case DIK_R: // reset
		CGame::GetInstance()->InitiateSwitchScene(5);
		break;
	
	case DIK_A:
		CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
		if (mario->getlevel() == MARIO_LEVEL_TAIL)
		{
			if (mario->GetState() != MARIO_STATE_SIT)
			{
				if (mario->getnx() > 0)
					mario->SetState(MARIO_STATE_ATTACK_RIGHT);
				else
					mario->SetState(MARIO_STATE_ATTACK_LEFT);
			}
		}
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (!mario)
		return;
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A: // key up => reset prepare to run
	{
		
		break;
	}
	case DIK_X:
	{
		
		mario->SetIsFlying(false);
		mario->setIsOnPlatForm(true);
		
		break;
	}
	case DIK_RIGHT:
		
		break;
	case DIK_LEFT:
		
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (!mario)
		return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		// if press A => in first 2 - 3 second Mario will run with velocity : 0.08f, then velocity is 0.2f
		if (game->IsKeyDown(DIK_A))
		{
			//at the first time into this state we'll have an boolean variable to count the time [isReady]
			if (mario->GetState() !=  MARIO_STATE_PREPARE_RUNNING_RIGHT)
			{
				if (mario->GetState() !=  MARIO_STATE_RUNNING_RIGHT)
				{
					if (mario->GetState() != MARIO_STATE_RELEASE_FLYING)
					{
						if (mario->GetState() != MARIO_STATE_FLYING)
						{
							if (mario->GetState() == MARIO_STATE_RUNNING_LEFT)
								mario->setIsSwitch(true);
							if (mario->GetState() != MARIO_STATE_JUMP)
								mario->SetState(MARIO_STATE_PREPARE_RUNNING_RIGHT);
						}
						else
						{
							// case mario change direction when flying and not time out
							if (GetTickCount64() - mario->getFlyingStart() < 4000 )
							{
								if (mario->getnx() < 0)
								{
									if (mario->getIsOnPlatForm() == false)
									{
										mario->setNx(1);
										mario->SetVy(-MARIO_WALKING_SPEED);
										mario->Setax(MARIO_ACCEL_RUN_X);
										mario->setMaxVx(MARIO_RUNNING_SPEED - 0.03f);
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			if (mario->GetState() != MARIO_STATE_FLYING)
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
			else
			{
				mario->setMaxVx(MARIO_WALKING_SPEED);
				mario->Setax(MARIO_ACCEL_WALK_X);
			}
		}
		

		//flying
		if (game->IsKeyDown(DIK_X))
		{
			if (mario->GetState() != MARIO_STATE_RELEASE_FLYING) {
				if (mario->GetState() == MARIO_STATE_RUNNING_RIGHT)
				{
					if (mario->getlevel() == MARIO_LEVEL_TAIL)
					{
						if (mario->GetState() != MARIO_STATE_FLYING)
							mario->SetState(MARIO_STATE_FLYING);
					}
				}
				else if (mario->GetState() == MARIO_STATE_FLYING)
				{
					if (GetTickCount64() - mario->getFlyingStart() < 4000)
					{
						//write for fun
						if (game->IsKeyDown(DIK_A) == false)
						{
							if (mario->getnx() < 0)
							{
								mario->setNx(1);

							}
							mario->setIsOnPlatForm(true);
							mario->SetVy(-MARIO_WALKING_SPEED);
							mario->Setax(MARIO_ACCEL_RUN_X);
							mario->setMaxVx(MARIO_WALKING_SPEED);
						}
						else
						{
							mario->setIsOnPlatForm(true);
							mario->SetVy(-MARIO_WALKING_SPEED);
							mario->Setax(MARIO_ACCEL_RUN_X);
							mario->setMaxVx(MARIO_RUNNING_SPEED -0.03f);
						}
						
						
					}
				}
			}
		}
		
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (mario->GetState() !=  MARIO_STATE_PREPARE_RUNNING_LEFT)
			{
				if (mario->GetState() !=  MARIO_STATE_RUNNING_LEFT)
				{
					if (mario->GetState() != MARIO_STATE_RELEASE_FLYING)
					{
						if (mario->GetState() != MARIO_STATE_FLYING)
						{
							if (mario->GetState() == MARIO_STATE_RUNNING_RIGHT)
								mario->setIsSwitch(true);
							if (mario->GetState() != MARIO_STATE_JUMP)
								mario->SetState(MARIO_STATE_PREPARE_RUNNING_LEFT);
						}
						else
						{
							if (GetTickCount64() - mario->getFlyingStart() < 4000 )
							{
								if (mario->getnx() > 0)
								{
									if (mario->getIsOnPlatForm() == false)
									{
										mario->setNx(-1);
										mario->SetVy(-MARIO_WALKING_SPEED);
										mario->Setax(-MARIO_ACCEL_RUN_X);
										mario->setMaxVx(-MARIO_RUNNING_SPEED + 0.03f);
									}
								}
								
							}
						}
					}
				}
			}
		}
		else {
			if (mario->GetState() != MARIO_STATE_FLYING)
				mario->SetState(MARIO_STATE_WALKING_LEFT);
			else
			{
				mario->setMaxVx(-MARIO_WALKING_SPEED);
				mario->Setax(-MARIO_ACCEL_WALK_X);
			}
		}
		// flying
		if (game->IsKeyDown(DIK_X))
		{
			if (mario->GetState() != MARIO_STATE_RELEASE_FLYING)
			{
				if (mario->GetState() == MARIO_STATE_RUNNING_LEFT)
				{
					if (mario->getlevel() == MARIO_LEVEL_TAIL)
					{
						if (mario->GetState() != MARIO_STATE_FLYING)
							mario->SetState(MARIO_STATE_FLYING);
					}
				}
				else if (mario->GetState() == MARIO_STATE_FLYING)
				{
					if (GetTickCount64() - mario->getFlyingStart() < 4000)
					{
						if (game->IsKeyDown(DIK_A) == false )
						{
							if (mario->getnx() > 0)
							{
								mario->setNx(-1);
							}
							mario->setIsOnPlatForm(true);
							mario->SetVy(-MARIO_WALKING_SPEED);
							mario->Setax(-MARIO_ACCEL_RUN_X);
							mario->setMaxVx(-MARIO_WALKING_SPEED);
						}
						else
						{
							mario->setIsOnPlatForm(true);
							mario->SetVy(-MARIO_WALKING_SPEED);
							mario->Setax(-MARIO_ACCEL_RUN_X);
							mario->setMaxVx(-MARIO_RUNNING_SPEED + 0.03f);
						}
						
					}
				}
			}
		}
	}
	else
	{
		if(mario->GetState() != MARIO_STATE_FLYING)
			mario->SetState(MARIO_STATE_IDLE);
	}
}