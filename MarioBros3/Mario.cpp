﻿#include <algorithm>
#include "debug.h"
#include "RedMushroom.h"
#include "Mario.h"
#include "Game.h"
#include"GameObject.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBlock.h"
#include "Collision.h"
#include "Bullet.h"
#include "PiranhaPlant.h"
#include "Koopas.h"
#include "ColorBox.h"
#include "Leaf.h"
#include "Leaf.h"
#include "Platform.h"
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//ay = MARIO_GRAVITY;
	if(!isFlying)
		vy += ay * dt;
	vx += ax * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	
	if (GetTickCount64() - attack_start > MARIO_ATTACK_TIME)
	{
		//DebugOut(L"time out");
		isAttackByTail = false;
		attack_start = 0;
	}
	if (state == MARIO_STATE_PREPARE_RUNNING_LEFT || state == MARIO_STATE_PREPARE_RUNNING_RIGHT)
	{
		if (GetTickCount64() - running_start > MARIO_TIME_TO_RUN)
		{
			if (state == MARIO_STATE_PREPARE_RUNNING_LEFT)
			{
				SetState(MARIO_STATE_RUNNING_LEFT);
			}
			else if (state == MARIO_STATE_PREPARE_RUNNING_RIGHT)
			{
				SetState(MARIO_STATE_RUNNING_RIGHT);
			}
			running_start = 0;
			isRun = true;
		}

		/*if (isFlying)
		{
			if (GetTickCount64() - flying_start > MARIO_FLYING_TIME)
			{
				if(nx > 0)
					SetState(MARIO_STATE_RELEASE_FLYING_RIGHT);
				else
					SetState(MARIO_STATE_RELEASE_FLYING_LEFT);
			}
			isFlying = false;
		}*/
		/*if (isOnPlatform)
		{
			if (nx > 0)
				SetState(MARIO_STATE_RUNNING_RIGHT);
			else					 
				SetState(MARIO_STATE_RUNNING_LEFT);
		}*/
	}
	

	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 )
	{
		if (e->obj->IsBlocking())
		{
			vy = 0;
			if (e->ny < 0) isOnPlatform = true;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
	
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CRedMushroom*>(e->obj))
		OnCollisionWithRedMushRoom(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithRedBullet(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithRedPiranhaPlant(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);	
	else if (dynamic_cast<CPlatform*>(e->obj))
	{
		CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
		if (platform->IsBlocking() == 0 && platform->getIsBlockKoopas() == 0) {

			if (e->ny < 0) {

				isOnPlatform = true;
				SetYWhenCollideColorbox(platform);
			}
		}
	}
}

void CMario::SetYWhenCollideColorbox(LPGAMEOBJECT gameobject) {
	if (level == MARIO_LEVEL_SMALL) {
		if (gameobject->gety() - gety() < MARIO_SMALL_BBOX_HEIGHT + 8.0f)
		{
			sety(gameobject->gety() - MARIO_SMALL_BBOX_HEIGHT - 4.0f);
			vy = 0; 
			isOnPlatform = true;
		}
	}
	else {
		if (!isSitting) {
			if (gameobject->gety() - gety() < MARIO_BIG_BBOX_HEIGHT )
			{
				sety(gameobject->gety() - MARIO_BIG_BBOX_HEIGHT + 4);
				vy = 0;
				isOnPlatform = true;
			}
		}
		else {
			if (gameobject->gety() - gety() < MARIO_BIG_BBOX_HEIGHT / 2 + 4)
			{
				sety(gameobject->gety() - MARIO_BIG_BBOX_HEIGHT / 2 - 4);
				vy = 0;
				isOnPlatform = true;
			}
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithRedMushRoom(LPCOLLISIONEVENT e)
{
	this->SetLevel(MARIO_LEVEL_BIG);
	e->obj->Delete();
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	CQuestionBlock* p = dynamic_cast<CQuestionBlock*>(e->obj);
	if (e->ny > 0 && p->GetState() == QUESTIONBLOCK_STATE_NONE_EMPTY)
	{
		p->SetState(QUESTIONBLOCK_STATE_EMPTY);
		
		if (p->getType() == 1)
		{
			CCoin* t = new CCoin(p->getx(), p->gety() - 25.0f, 1);
			scene->AddObject(t);
		}
		else if (p->getType() == 2) // question block contains item
		{
			if (level == MARIO_LEVEL_SMALL)
			{
				CRedMushroom* mushroom = new CRedMushroom(x, y - 95.0f);
				scene->AddObject(mushroom);
			}
			else  if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_TAIL)
			{
				CLeaf* leaf = new CLeaf(x, y - 35.0f);
				scene->AddObject(leaf);
			}
		}

	}

}

void CMario::OnCollisionWithRedBullet(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_TAIL)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;

			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			e->src_obj->SetState(MARIO_STATE_DIE);

		}
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithRedPiranhaPlant(LPCOLLISIONEVENT e)
{

	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_TAIL)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			e->src_obj->SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	// jump on top >> kill Koopas and deflect a bit 
	//we got four case col
	if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT || koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
	{
		DebugOut(L"kill this koopas");
		if (e->ny < 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_DIE_DOWN)
			{
				koopas->SetState(KOOPAS_STATE_DIE_DOWN);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else if (e->nx != 0)
		{
			
			if (untouchable == 0)
			{
				if (level == MARIO_LEVEL_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					SetState(MARIO_STATE_DIE);

				}
			}
		}
	}

	else if (koopas->GetState() == KOOPAS_STATE_DIE_DOWN || koopas->GetState() == KOOPAS_STATE_DIE_UP)
	{
		if (x < koopas->getx())
			koopas->setVx(abs(KOOPAS_SPINNING_SPEED));
		else
			koopas->setVx(-abs(KOOPAS_SPINNING_SPEED));
		koopas->sety(koopas->gety() - 5.0f);
		koopas->SetState(KOOPAS_STATE_DIE_DOWN_SPIN);

	}
	else if (koopas->GetState() == KOOPAS_STATE_DIE_UP_SPIN || koopas->GetState() == KOOPAS_STATE_DIE_DOWN_SPIN)
	{
		// make defend koopas stop
		if (e->ny != 0)
		{
			koopas->sety(koopas->gety() - 9.0f);
			koopas->SetState(KOOPAS_STATE_DIE_DOWN);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (e->nx != 0)
		{
			if (untouchable == 0)
			{
				if (level == MARIO_LEVEL_TAIL)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	SetLevel(MARIO_LEVEL_TAIL);
	e->obj->Delete();
}


//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}

	}
	else
	{
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if(!isRun)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (!isRun)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
					else
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
	}
	
	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) {
					if (!isRun)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
					else
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				}
					
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if(!isRun)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
					else
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;
	if (!isFlying)
	{
		if (!isAttackByTail)
		{
			if (!isOnPlatform)
			{
				DebugOut(L"VO KHONG PHAI PLATFORM\n");
				if (isReleaseFlying)
				{
					DebugOut(L"VO RELEASE\n");

					if (nx >= 0)
						aniId = ID_ANI_MARIO_TAIL_LOW_FLYING_RIGHT;
					else
						aniId = ID_ANI_MARIO_TAIL_LOW_FLYING_LEFT;
				}
				else
				{
					if (abs(ax) == MARIO_ACCEL_RUN_X)
					{
						if (nx >= 0)
							aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT;
						else
							aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT;
					}
					else
					{
						if (nx >= 0)
							aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT;
						else
							aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT;
					}
				}
			}
			else
				if (isSitting)
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_TAIL_SIT_RIGHT;
					else
						aniId = ID_ANI_MARIO_TAIL_SIT_LEFT;
				}
				else
				{
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_TAIL_IDLE_LEFT;
					}
					else if (vx > 0)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_TAIL_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X)
						{
							if (!isRun)
								aniId = ID_ANI_MARIO_TAIL_WALKING_RIGHT;
							else
								aniId = ID_ANI_MARIO_TAIL_RUNNING_RIGHT;
						}
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_TAIL_WALKING_RIGHT;
					}
					else // vx < 0
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_TAIL_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X)
						{
							if (!isRun)
								aniId = ID_ANI_MARIO_TAIL_WALKING_LEFT;
							else
								aniId = ID_ANI_MARIO_TAIL_RUNNING_LEFT;
						}
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_TAIL_WALKING_LEFT;
					}

				}
		}
		else
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TAIL_ATTACK_RIGHT;
			else if (nx < 0)
				aniId = ID_ANI_MARIO_TAIL_ATTACK_LEFT;
		}


		if (aniId == -1)
		{
			aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
		}
	}
	else
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_TAIL_FLYING_RIGHT;
		else
			aniId = ID_ANI_MARIO_TAIL_FLYING_LEFT;
	}

	return aniId;
}


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TAIL)
		aniId = GetAniIdTail();
	animations->Get(aniId)->Render(x, y);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{	
	case MARIO_STATE_RELEASE_FLYING_RIGHT:
		isReleaseFlying = true;
		vx = MARIO_WALKING_SPEED;
		vy = MARIO_GRAVITY ;
		break;
	case MARIO_STATE_RELEASE_FLYING_LEFT:
		isReleaseFlying = true;
		vx = -MARIO_WALKING_SPEED;
		vy = MARIO_GRAVITY ;
		break;
	case MARIO_STATE_FLYING_RIGHT:
		isFlying = true;
		flying_start = GetTickCount64();
		vx = MARIO_WALKING_SPEED;
		vy = -MARIO_WALKING_SPEED;
		break;
	case MARIO_STATE_FLYING_LEFT:
		isFlying = true;
		flying_start = GetTickCount64();
		vx = -MARIO_WALKING_SPEED;
		vy = -MARIO_WALKING_SPEED;
		break;
	case MARIO_STATE_PREPARE_RUNNING_RIGHT:
		if (isSitting) break;
		if (!isReadyToRun)
		{
			running_start = GetTickCount64();
			isReadyToRun = true;
		}
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_PREPARE_RUNNING_LEFT:
		if (isSitting) break;
		if (!isReadyToRun)
		{
			running_start = GetTickCount64();
			isReadyToRun = true;
		}
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	/*case MARIO_STATE_LOW_FLY:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y + 0.05F;
			else
				vy = -MARIO_JUMP_SPEED_Y + 0.05F;
		}
		break;*/
	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_ATTACK_RIGHT:
		isAttackByTail = true;
		attack_start = GetTickCount64();
		nx = 1;
		break;
	case MARIO_STATE_ATTACK_LEFT:
		isAttackByTail = true;
		attack_start = GetTickCount64();
		nx = -1;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG ||  level == MARIO_LEVEL_TAIL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2 ;
	}
	level = l;

}

