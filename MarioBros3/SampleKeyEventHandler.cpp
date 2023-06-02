#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "MarioStop.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

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
					DebugOut(L"jo %d\n ", a->getCanMoveUp());
					
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
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	/*case DIK_X:
		mario->SetState(MARIO_STATE_LOW_FLY);
		break;*/
	case DIK_A:
		CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
		if (mario->getlevel() == MARIO_LEVEL_TAIL)
		{
			if(mario->getnx() > 0)
				mario->SetState(MARIO_STATE_ATTACK_RIGHT);
			else
				mario->SetState(MARIO_STATE_ATTACK_LEFT);
		}
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A: // key up => reset prepare to run
		if (mario->GetState() != MARIO_STATE_FLYING_RIGHT && mario->GetState() != MARIO_STATE_FLYING_LEFT)
		{
			mario->SetIsRun(false);
			mario->SetIsReadyToRun(false);
		}
		else
		{
			mario->SetIsFlying(false);
			mario->SetIsReleaseFlying(true);
			DebugOut(L"hello %d\n", mario->GetState());
			if (mario->GetState() == MARIO_STATE_FLYING_RIGHT || mario->GetState() == MARIO_STATE_FLYING_LEFT)
			{
				DebugOut(L"hello ");
				if (mario->getnx() > 0)
					mario->SetState(MARIO_STATE_RELEASE_FLYING_RIGHT);
				else
					mario->SetState(MARIO_STATE_RELEASE_FLYING_LEFT);
			}
		}
		break;
	case DIK_X:
		mario->SetIsFlying(false);
		mario->SetIsReleaseFlying(true);
		DebugOut(L"hello %d\n", mario->GetState());
		if (mario->GetState() == MARIO_STATE_FLYING_RIGHT || mario->GetState() == MARIO_STATE_FLYING_LEFT)
		{
			DebugOut(L"hello ");
			if (mario->getnx() > 0)
				mario->SetState(MARIO_STATE_RELEASE_FLYING_RIGHT);
			else
				mario->SetState(MARIO_STATE_RELEASE_FLYING_LEFT);
		}
		break;
	case DIK_RIGHT:
		mario->SetIsRun(false);
		mario->SetIsReadyToRun(false);
		break;
	case DIK_LEFT:
		mario->SetIsRun(false);
		mario->SetIsReadyToRun(false);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (mario->getIsRun() == 0)
			{
				mario->SetState(MARIO_STATE_PREPARE_RUNNING_RIGHT);
			}
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);

		if (game->IsKeyDown(DIK_X))
		{
			if (mario->GetState() == MARIO_STATE_RUNNING_RIGHT || mario->GetState() == MARIO_STATE_RELEASE_FLYING_RIGHT )
			{
				if (mario->getlevel() == MARIO_LEVEL_TAIL)
				{
					mario->SetState(MARIO_STATE_FLYING_RIGHT);
				}
			}
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (mario->getIsRun() == 0)
			{
				mario->SetState(MARIO_STATE_PREPARE_RUNNING_LEFT);
			}
		}
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);

		if (game->IsKeyDown(DIK_X))
		{
			if (mario->GetState() == MARIO_STATE_RUNNING_LEFT || mario->GetState() == MARIO_STATE_RELEASE_FLYING_LEFT)
			{
				if (mario->getlevel() == MARIO_LEVEL_TAIL)
				{
					mario->SetState(MARIO_STATE_FLYING_LEFT);
				}
			}
		}
	}
	
	else
		mario->SetState(MARIO_STATE_IDLE);
}