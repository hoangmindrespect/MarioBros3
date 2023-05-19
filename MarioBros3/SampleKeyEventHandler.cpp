#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
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
		mario->SetIsRun(false);
		mario->SetIsReadyToRun(false);
		break;
	case DIK_X:
		mario->SetIsFlying(false);
		if (mario->getnx() > 0)
			mario->SetState(MARIO_STATE_RELEASE_FLYING_RIGHT);
		else
			mario->SetState(MARIO_STATE_RELEASE_FLYING_LEFT);
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
				mario->SetState(MARIO_STATE_FLYING_RIGHT);
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
				mario->SetState(MARIO_STATE_FLYING_LEFT);
			}
		}
	}
	
	else
		mario->SetState(MARIO_STATE_IDLE);
}