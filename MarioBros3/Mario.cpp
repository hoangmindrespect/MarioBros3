#include <algorithm>
#include "debug.h"
#include "Mushroom.h"
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
#include "Effect.h"
#include "Goal.h"
#include "RedGoomba.h"
#include "RedGoomba.h"
#include "HUD.h"
#include "Funnel.h"
#include "PSwitch.h"
#include "Intro.h"
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (IsInMap == 0)
	{
		if(!isFlying && !isRealse)
			vy += ay * dt;
		vx += ax * dt;
		if (abs(vx) > abs(maxVx) && isSwitch == false)
		{
				vx = maxVx;
		}
		if ((vx > 0 && ax > 0) || (vx < 0 && ax < 0))
			isSwitch = false;
		
		// reset untouchable timer if untouchable time has passed
		if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
		
		if (CPlayScene::IsIntroScene())
		{
			//DebugOut(L"hi");
			if (isFellOnTheHead)
			{
				if (GetTickCount64() - time_switching > 300)
				{
					isFellOnTheHead = false;
					time_switching = GetTickCount64();
					isLookUp = true;
				}
			}

			if (isLookUp)
			{
				if (GetTickCount64() - time_switching > 500)
				{
					isLookUp = false;
				}
			}
		}

		if (state == MARIO_STATE_DIE)
		{
			if (GetTickCount64() - die_start > 2000)
			{
				CGame::GetInstance()->InitiateSwitchScene(1); 
				die_start = 0;
			}
		}

		if (state == MARIO_STATE_FLYING)
		{
			if (GetTickCount64() - flying_start > 6000)
			{
				SetState(MARIO_STATE_RELEASE_FLYING);
				isFlying = false;
				isRealse = true;
				flying_start = 0;
			}
			else
				count_time_prepare_running = 1900;
		}
		if (GetTickCount64() - attack_start > MARIO_ATTACK_TIME)
		{
			isAttackByTail = false;
			attack_start = 0;
		}
		
		if (state == MARIO_STATE_PREPARE_RUNNING_LEFT || state == MARIO_STATE_PREPARE_RUNNING_RIGHT)
		{
			count_time_prepare_running = GetTickCount64() - running_start;
			if (pre_count_time_prepare_running > 0)
			{
				count_time_prepare_running += pre_count_time_prepare_running;
				pre_count_time_prepare_running = 0;
			}
			if (count_time_prepare_running > 1800)
			{
				if(nx > 0)
					SetState(MARIO_STATE_RUNNING_RIGHT);
				else
					SetState(MARIO_STATE_RUNNING_LEFT);
				running_start = -1;
				count_time_prepare_running = 1800;
			}
		}
		else
		{
			if (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT)
			{
				count_time_prepare_running = 1800;
			}
			else
			{
				if (count_time_prepare_running > 0)
				{
					if (count_time_prepare_running - 40 < 0)
					{
						count_time_prepare_running = 0;
					}
					else
					{
						count_time_prepare_running -= 40;
					}
					pre_count_time_prepare_running = count_time_prepare_running;
				}
			}
		}
		
		if (isHolding)
		{
			LPGAME game = CGame::GetInstance();
			if (!game->IsKeyDown(DIK_A))
			{
				isHolding = false;
				isKicking = true;
				kicking_start = GetTickCount64();
				if(Koopas)
					KickKoopas(Koopas, this);

			}
			else // if keep pressing DIK_A and koopas time out
			{
				if (Koopas)
				{
					if (GetTickCount64() - Koopas->getDieStart() > KOOPAS_DIE_TIMEOUT + 2000)
					{
						isHolding = false;
						DeLevel(this);
					}
				}
			}
		}

		if (isOnPlatform)
		{
			isRealse = false;
		}
		
	}
	else
	{
		vy = vx = 0.0f;
		if (isMoveDown == true)
		{
			if (isEndTurn == false)
			{
				ytmp = y + DISTANCE_MOVING_IN_MAP;
				isEndTurn = true;
			}

			if (y <= ytmp) {
				y += dt * MARIO_MOVING_IN_MAP_SPEED;

			}
			else
			{
				y = ytmp;
				vy = 0.0f;
				isEndTurn = false;
				isMoveDown = false;
			}
		}
		else if (isMoveUp == true)
		{
			if (isEndTurn == false)
			{
				ytmp = y - DISTANCE_MOVING_IN_MAP;
				isEndTurn = true;
			}
			if (y > ytmp)
				y -= dt * MARIO_MOVING_IN_MAP_SPEED;
			else
			{
				vy = 0.0f;
				y = ytmp;
				isEndTurn = false;
				isMoveUp = false;
			};
		}
		else if (isMoveRight == true)
		{
			if (isEndTurn == false)
			{
				xtmp = x + DISTANCE_MOVING_IN_MAP;
				isEndTurn = true;
			}
			if (x <= xtmp)
				x += MARIO_MOVING_IN_MAP_SPEED * dt;
			else
			{
				vx = 0.0f;
				x = xtmp;
				isEndTurn = false;
				isMoveRight = false;
			};
		}
		else if (isMoveLeft == true)
		{
			if (isEndTurn == false)
			{
				xtmp = x - DISTANCE_MOVING_IN_MAP;
				isEndTurn = true;
			}
			if (x > xtmp)
				x -= MARIO_MOVING_IN_MAP_SPEED * dt;
			else
			{
				vx = 0.0f;
				x = xtmp;
				isEndTurn = false;
				isMoveLeft = false;
			};
		}
	}

	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
	if (Tail)
	{
		Tail->setVx(vx);
		Tail->setVy(vy);
		if (nx > 0)
		{
			Tail->setx(x);
			Tail->sety(y + 6.0f);
		}
		else
		{
			Tail->setx(x);
			Tail->sety(y + 6.0f);
		}
	}
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
			if (e->ny < 0) {
				isOnPlatform = true;
				isFlying = false;
				if (state == MARIO_STATE_FLYING)
				{
					if (nx > 0)
					{
						SetState(MARIO_STATE_RUNNING_RIGHT);
					}
					else
					{
						SetState(MARIO_STATE_RUNNING_LEFT);
					}
				}
			}
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		if (mario->getColor() == 1)
		{
			CMario* mario = dynamic_cast<CMario*>(e->obj);
			mario->setIsOnPlatForm(true);
			mario->SetState(MARIO_STATE_SIT);
			mario->SetVx(0.0f);
			mario->Setax(0.0f);
			mario->sety(mario->gety() - 1.0f);
			CIntro::isHitMario = true;
		}
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
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
	else if (dynamic_cast<CGoal*>(e->obj))
		OnCollisionWithGoal(e);
	else if (dynamic_cast<CRedGoomba*>(e->obj))
		OnCollisionWithRedGoomba(e);
	else if (dynamic_cast<CFunnel*>(e->obj))
		OnCollisionWithFunnel(e);
	else if (dynamic_cast<CPSwitch*>(e->obj))
		OnCollisionWithPSwitch(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_KOOPAS)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			// in this time: MARIO in state release flying so vy is const -> 
			if (CPlayScene::IsIntroScene())
			{
				SetIsRelease(false);
				SetState(MARIO_STATE_JUMP);
				vy = -0.1f;
				return;
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			CPlayScene::point += 100;
			CEffect* a = new CEffect(goomba->getx(), goomba->gety(), 6);
			CPlayScene::objects.push_back(a);
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_KOOPAS)
			{
				DeLevel(this);
			}
		}
	}
}

void CMario::OnCollisionWithRedGoomba(LPCOLLISIONEVENT e)
{
	CRedGoomba* goomba = dynamic_cast<CRedGoomba*>(e->obj);
	if (e->ny < 0)
	{
		if (goomba->GetState() != RED_GOOMBA_STATE_DIE && goomba->GetState() != RED_GOOMBA_STATE_DIE_BY_KOOPAS)
		{
			if (goomba->GetState() == RED_GOOMBA_STATE_WALKING_NONE_WINGS)
			{
				goomba->SetState(RED_GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				CPlayScene::point += 100;
				CEffect* a = new CEffect(goomba->getx(), goomba->gety(), 6);
				CPlayScene::objects.push_back(a);
			}
			else //with wings
			{
				goomba->SetState(RED_GOOMBA_STATE_WALKING_NONE_WINGS);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				CPlayScene::point += 100;
				CEffect* a = new CEffect(goomba->getx(), goomba->gety(), 6);
				CPlayScene::objects.push_back(a);
			}
		}
	}
	else // hit by RED Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_BY_KOOPAS)
			{
				DeLevel(this);
			}
		}
	}
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CPlayScene::coin += 1;
	CPlayScene::point += 50;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	if(isSwitch)
		CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());;
}

void CMario::OnCollisionWithRedMushRoom(LPCOLLISIONEVENT e)
{
	CRedMushroom* mus = dynamic_cast<CRedMushroom*>(e->obj);
	if (mus->getType() == 1)
	{
		this->SetLevel(MARIO_LEVEL_BIG);
		isChanging = true;
		time_switching = GetTickCount64();
		CPlayScene::point += 1000;
		CEffect* a = new CEffect(x, y - MARIO_BIG_BBOX_HEIGHT / 2, 7);
		CPlayScene::objects.push_back(a);
	}
	else
	{
		CPlayScene::turn += 1;
		CEffect* a = new CEffect(x, y - MARIO_BIG_BBOX_HEIGHT / 2, 11);
		CPlayScene::objects.push_back(a);
	}
	e->obj->Delete();
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	CQuestionBlock* p = dynamic_cast<CQuestionBlock*>(e->obj);
	if (e->ny > 0 && p->GetState() == QUESTIONBLOCK_STATE_NONE_EMPTY)
	{
		CPlayScene::point += 100;
		p->SetState(QUESTIONBLOCK_STATE_EMPTY);
		
		if (p->getType() == 1)
		{
			CCoin* t = new CCoin(p->getx(), p->gety() - 15.0f, 1);
			scene->AddObject(t);
			CPlayScene::coin += 1;
		}
		else if (p->getType() == 2) // question block contains item
		{
			if (level == MARIO_LEVEL_SMALL)
			{
				CRedMushroom* mushroom = new CRedMushroom(p->getx(), p->gety(), 1);
				scene->AddObject1(mushroom);
			}
			else  if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_TAIL)
			{
				CLeaf* leaf = new CLeaf(p->getx(), p->gety() - 55.0f);
				scene->AddObject(leaf);
			}
		}
		else if (p->getType() == 3)
		{
			CPSwitch* pswitch =new CPSwitch(p->getx(), p->gety() - 16.0f);
			scene->AddObject(pswitch);
		}
		else if (p->getType() == 4)
		{
			CRedMushroom* mushroom = new CRedMushroom(p->getx(), p->gety(), 2);
			scene->AddObject1(mushroom);
		}
	}
}

void CMario::OnCollisionWithRedBullet(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		DeLevel(this);
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithRedPiranhaPlant(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		DeLevel(this);
	}
}

void CMario::OnCollisionWithGoal(LPCOLLISIONEVENT e)
{
	CGoal* a = dynamic_cast<CGoal*>(e->obj);
	a->setIsCollide(true);
	isEndScene = true;
}
void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	// jump on top >> kill Koopas and deflect a bit 
	//we got five case collide
	if (koopas->GetState() == JUMP_KOOPAS_STATE_JUMPING)
	{
		if (e->ny < 0)
		{
			if (koopas->getnx() > 0)
			{
				koopas->SetState(KOOPAS_STATE_WALKING_RIGHT);
			}
			else
				koopas->SetState(KOOPAS_STATE_WALKING_LEFT);
			CPlayScene::point += 100;
			CEffect* a = new CEffect(koopas->getx(), koopas->gety(), 6);
			CPlayScene::objects.push_back(a);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (e->nx != 0)
		{
			if (untouchable == 0)
				DeLevel(this);
		}
	}
	else if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT || koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
	{
		if (e->ny < 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_DIE_DOWN)
			{
				koopas->SetState(KOOPAS_STATE_DIE_DOWN);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				CPlayScene::point += 100;
				CEffect* a = new CEffect(koopas->getx(), koopas->gety(), 6);
				CPlayScene::objects.push_back(a);
			}
		}
		else if (e->nx != 0)
		{
			if (untouchable == 0)
				DeLevel(this);
		}
	}
	else if (koopas->GetState() == KOOPAS_STATE_DIE_DOWN || koopas->GetState() == KOOPAS_STATE_DIE_UP || koopas->GetState() == KOOPAS_STATE_RETURN_DOWN || koopas->GetState() == KOOPAS_STATE_RETURN_UP || state == KOOPAS_STATE_FALL_INTO_MARIO)
	{
		LPGAME game = CGame::GetInstance();
		if (e->ny > 0)
		{
			if (CPlayScene::IsIntroScene())
			{
				if (koopas->GetState() == KOOPAS_STATE_DIE_DOWN)
				{
					time_switching = GetTickCount64();
					koopas->SetState(KOOPAS_STATE_FALL_INTO_MARIO);
					isFellOnTheHead = true;
					return;
				}
			}
		}	

		//kick: die + collide + not pressA => kick
		if (!game->IsKeyDown(DIK_A))
		{
			if (x < koopas->getx())
				koopas->setVx(abs(KOOPAS_SPINNING_SPEED));
			else
				koopas->setVx(-abs(KOOPAS_SPINNING_SPEED));
			koopas->sety(koopas->gety() - 5.0f);
			
			isKicking = true;
			kicking_start = GetTickCount64();
			if(koopas->GetState() == KOOPAS_STATE_DIE_DOWN || koopas->GetState() == KOOPAS_STATE_RETURN_DOWN || state == KOOPAS_STATE_FALL_INTO_MARIO)
				koopas->SetState(KOOPAS_STATE_DIE_DOWN_SPIN);
			else
				koopas->SetState(KOOPAS_STATE_DIE_UP_SPIN);
		}
		else
		{
			if (koopas->GetState() == KOOPAS_STATE_DIE_DOWN)
			{
				koopas->SetState(KOOPAS_STATE_IS_HOLD_DOWN);
			}
			else if (koopas->GetState() == KOOPAS_STATE_DIE_UP)
				koopas->SetState(KOOPAS_STATE_IS_HOLD_UP);
			isHolding = true; Koopas = koopas;
		}
	}
	else if (koopas->GetState() == KOOPAS_STATE_DIE_UP_SPIN || koopas->GetState() == KOOPAS_STATE_DIE_DOWN_SPIN)
	{
		// make defend koopas stop
		if (e->ny != 0)
		{
			koopas->sety(koopas->gety() - 7.0f);
			if (koopas->GetState() == KOOPAS_STATE_DIE_DOWN_SPIN)
				koopas->SetState(KOOPAS_STATE_DIE_DOWN);
			else
				koopas->SetState(KOOPAS_STATE_DIE_UP);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (e->nx != 0)
		{
			if (untouchable == 0)
			{
				DeLevel(this);
			}
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	if (CPlayScene::IsIntroScene())
	{
		SetLevel(MARIO_LEVEL_TAIL);
	}
	else
	{
		if (level != MARIO_LEVEL_TAIL)
		{
			SetLevel(MARIO_LEVEL_TAIL);
			isChanging = true;
			time_switching = GetTickCount64();
		}
		CPlayScene::point += 1000;
		CEffect* a = new CEffect(x, y - MARIO_BIG_BBOX_HEIGHT / 2, 7);
		CPlayScene::objects.push_back(a);
	}
	e->obj->Delete();
}

void  CMario::OnCollisionWithFunnel(LPCOLLISIONEVENT e)
{
	LPGAME game = CGame::GetInstance();
	CFunnel* funnel = dynamic_cast<CFunnel*>(e->obj);
	if (game->IsKeyDown(DIK_UP))
	{
		isGetInOutPipe = true;
		CPlayScene::isGetInUp = true;
		CPlayScene::tempoPosition = y - 18.0f;
		CPlayScene::time_start = GetTickCount64();
		CPlayScene::X_target = funnel->getXTarget();
		CPlayScene::Y_target = funnel->getYTarget();
	}
	if (game->IsKeyDown(DIK_DOWN))
	{
		isGetInOutPipe = true;
		CPlayScene::isGetInDown = true;
		CPlayScene::tempoPosition = y + 18.0f;
		CPlayScene::time_start = GetTickCount64();
		CPlayScene::X_target = funnel->getXTarget();
		CPlayScene::Y_target = funnel->getYTarget();
	}
}

void  CMario::OnCollisionWithPSwitch(LPCOLLISIONEVENT e)
{
	CPSwitch* ps = dynamic_cast<CPSwitch*>(e->obj);
	if (e->ny < 0 && ps->GetState() != PSWITCH_STATE_CLICKED)
	{
		ps->SetState(PSWITCH_STATE_CLICKED);
		for (int i = 0; i < CPlayScene::objects.size(); i++)
		{
			if (dynamic_cast<CBrick*>(CPlayScene::objects[i]))
			{
				CBrick* a = dynamic_cast<CBrick*>(CPlayScene::objects[i]);
				if (a->getModel() == 2)
				{
					CCoin* coin = new CCoin(a->getx(), a->gety(), 3);
					CPlayScene::objects.push_back(coin);
					a->Delete();
				}
			}
		}
	}
	
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!IsInMap)
	{
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
					{
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					}
					else if (ax == MARIO_ACCEL_RUN_X)
					{
						if(state == MARIO_STATE_PREPARE_RUNNING_RIGHT)
							aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
						else
							aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					}
					else if (ax == MARIO_ACCEL_WALK_X)
					{
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
					{
						if (state == MARIO_STATE_PREPARE_RUNNING_LEFT)
							aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
						else
							aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					}
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
		}
	}
	else
	{
		aniId = ID_ANI_MARIO_SMALL_IN_MAP;
	}
	
	if (isKicking)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
		if (GetTickCount64() - kicking_start > 200)
			isKicking = false;
	}
	if (isHolding)
	{
		if (isOnPlatform)
		{
			if (nx > 0)
			{
				if (vx != 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
			}
			else
			{
				if (vx != 0)
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
				else
					aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
			}
		}
		else
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
		}
	}

	if (isGetInOutPipe)
		aniId = ID_ANI_SMALL_MARIO_GET_INOUT_PIPE;
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
			{
				if(color == 1)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_GREEN_MARIO_JUMP_WALK_RIGHT;
			}
			else
			{
				if(color == 1)
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
				else 
					aniId = ID_ANI_GREEN_MARIO_JUMP_WALK_LEFT;
			}
		}

		if (isHolding)
		{
			if (isOnPlatform)
			{
				if (nx > 0)
				{
					if (vx != 0)
					{
						if(color == 1)
							aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
						else
							aniId = ID_ANI_GREEN_MARIO_HOLD_WALK_RIGHT;
					}
					else
					{
						if (color == 1)
							aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
						else
							aniId = ID_ANI_GREEN_MARIO_HOLD_IDLE_RIGHT;
					}
				}
				else
				{
					if (vx != 0)
					{
						if (color == 1)
							aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
						else
							aniId = ID_ANI_GREEN_MARIO_HOLD_WALK_LEFT;
					}
					else
					{
						if (color == 1)
							aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
						else
							aniId = ID_ANI_GREEN_MARIO_HOLD_IDLE_LEFT;
					}
				}
			}
			else
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
			}
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
		{
			if (vx == 0)
			{
				if (nx > 0) {
					if(color == 1)
						aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else
						aniId = ID_ANI_GREEN_MARIO_IDLE_RIGHT;
				}
				else {
					if(color == 1)
						aniId = ID_ANI_MARIO_IDLE_LEFT;
					else
						aniId = ID_ANI_GREEN_MARIO_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) {

					aniId = ID_ANI_MARIO_RUNNING_RIGHT;

				}

				else if (ax == MARIO_ACCEL_WALK_X)
				{
					if (state == MARIO_STATE_PREPARE_RUNNING_RIGHT)
						aniId = ID_ANI_MARIO_PREPARE_RIGHT;
					else
					{
						if (color == 1)
							aniId = ID_ANI_MARIO_WALKING_RIGHT;
						else
							aniId = ID_ANI_GREEN_MARIO_WALKING_RIGHT;
					}
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
				{
					if (state == MARIO_STATE_PREPARE_RUNNING_LEFT)
						aniId = ID_ANI_MARIO_PREPARE_LEFT;
					else
					{
						if(color == 1)
							aniId = ID_ANI_MARIO_WALKING_LEFT;
						else
							aniId = ID_ANI_GREEN_MARIO_WALKING_LEFT;
					}

				}
			}


			if (isKicking)
			{
				if (nx > 0)
				{
					if(color == 1)
						aniId = ID_ANI_MARIO_KICK_RIGHT;
					else
						aniId = ID_ANI_GREEN_MARIO_KICK_RIGHT;
				}
				else
				{
					if (color == 1)
						aniId = ID_ANI_MARIO_KICK_LEFT;
					else
						aniId = ID_ANI_GREEN_MARIO_KICK_LEFT;
				}				
				if (GetTickCount64() - kicking_start > 200)
					isKicking = false;
			}

			if (isHolding)
			{
				if (isOnPlatform)
				{
					if (nx > 0)
					{
						if (vx != 0)
						{
							if (color == 1)
								aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
							else
								aniId = ID_ANI_GREEN_MARIO_HOLD_WALK_RIGHT;
						}
						else
						{
							if (color == 1)
								aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
							else
								aniId = ID_ANI_GREEN_MARIO_HOLD_IDLE_RIGHT;
						}
					}
					else
					{
						if (vx != 0)
						{
							if (color == 1)
								aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
							else
								aniId = ID_ANI_GREEN_MARIO_HOLD_WALK_LEFT;
						}
						else
						{
							if (color == 1)
								aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
							else
								aniId = ID_ANI_GREEN_MARIO_HOLD_IDLE_LEFT;
						}
					}
				}
				else
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
				}
			}
		}
	}
	if (isChanging)
	{
		if (nx > 0)
			return aniId = ID_ANI_MARIO_UP_LEVEL_RIGHT;
		else
			return aniId = ID_ANI_MARIO_UP_LEVEL_BIG_LEFT;
	}
	if (CPlayScene::IsIntroScene())
	{
		if (isGetInOutPipe)
			aniId = ID_ANI_MARIO_GET_INOUT_PIPE;

		if (isFellOnTheHead)
			aniId = ID_ANI_MARIO_FELL_ON_THE_HEAD;
	}
	if (isLookUp)
		aniId = ID_ANI_MARIO_LOOKUP;

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_LEFT;

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
				if (!isRealse)
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
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_TAIL_LOW_FLYING_RIGHT;
					else
						aniId = ID_ANI_MARIO_TAIL_LOW_FLYING_LEFT;
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
						{
							aniId = ID_ANI_MARIO_TAIL_BRACE_RIGHT;
						}
						else if (ax == MARIO_ACCEL_RUN_X)
						{
							if (state == MARIO_STATE_PREPARE_RUNNING_RIGHT)
								aniId = ID_ANI_MARIO_TAIL_PREPARE_RUNNING_RIGHT;
							else
								aniId = ID_ANI_MARIO_TAIL_RUNNING_RIGHT;
						}
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_TAIL_WALKING_RIGHT;
					}
					else // vx < 0
					{
						if (ax > 0)
						{
							aniId = ID_ANI_MARIO_TAIL_BRACE_LEFT;
						}
						else if (ax == -MARIO_ACCEL_RUN_X)
						{
							if (state == MARIO_STATE_PREPARE_RUNNING_LEFT)
								aniId = ID_ANI_MARIO_TAIL_PREPARE_RUNNING_LEFT;
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
	}
	else
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_TAIL_FLYING_RIGHT;
		else
			aniId = ID_ANI_MARIO_TAIL_FLYING_LEFT;
	}

	if (isKicking)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_TAIL_KICK_RIGHT;
		else
			aniId = ID_ANI_MARIO_TAIL_KICK_LEFT;
		if (GetTickCount64() - kicking_start > 200)
			isKicking = false;
	}

	if (isHolding)
	{
		if (isOnPlatform)
		{
			if (nx > 0)
			{
				if(vx != 0)
					aniId = ID_ANI_MARIO_TAIL_HOLD_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_TAIL_HOLD_IDLE_RIGHT;
			}
			else
			{
				if(vx != 0)
					aniId = ID_ANI_MARIO_TAIL_HOLD_WALK_LEFT;
				else
					aniId = ID_ANI_MARIO_TAIL_HOLD_IDLE_LEFT;
			}
		}
		else
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TAIL_HOLD_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_TAIL_HOLD_JUMP_LEFT;
		}
	}

	if (isChanging)
		return aniId = ID_ANI_MARIO_UP_LEVEL_TAIL;
	if (isGetInOutPipe)
		aniId = ID_ANI_TAIL_MARIO_GET_INOUT_PIPE;

	if (aniId == -1)
	{
		aniId = ID_ANI_MARIO_TAIL_IDLE_LEFT;
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
	RenderBoundingBox();

}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{	
	case MARIO_STATE_RELEASE_FLYING: // it happen when time out
	{
		vy = MARIO_WALKING_SPEED;	
		if (nx > 0)
		{
			ax = MARIO_ACCEL_WALK_X;
			maxVx = MARIO_WALKING_SPEED;
		}
		else
		{
			ax = -MARIO_ACCEL_WALK_X;
			maxVx = -MARIO_WALKING_SPEED;
		}
		break;
	}
	case MARIO_STATE_FLYING:
	{
		flying_start = GetTickCount64();
		isFlying = true;
		vy = -MARIO_WALKING_SPEED;
		if (nx < 0)
		{
			maxVx = -MARIO_RUNNING_SPEED + 0.03f;
			ax = -MARIO_ACCEL_RUN_X;
		}
		else
		{
			maxVx = MARIO_RUNNING_SPEED - 0.03f;
			ax = MARIO_ACCEL_RUN_X;
		}
		break;
	}
	case MARIO_STATE_PREPARE_RUNNING_RIGHT:
	{
		if (isSitting) break;
		running_start = GetTickCount64();
		maxVx = MARIO_PREPARE_RUNNING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	}
	case MARIO_STATE_PREPARE_RUNNING_LEFT:
	{
		if (isSitting) break;
		running_start = GetTickCount64();
		maxVx = -MARIO_PREPARE_RUNNING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	}
	case MARIO_STATE_RUNNING_RIGHT:
	{
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	}
	case MARIO_STATE_RUNNING_LEFT:
	{
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	}
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
	case MARIO_STATE_RELEASE_JUMP:
	{
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		
		break;
	}

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
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
	if (level == MARIO_LEVEL_TAIL)
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
			if (state == MARIO_STATE_FLYING)
			{
				left = (x - (MARIO_TAIL_BBOX_WIDTH + 10.0f) / 2) + 2.0f;
				top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
				right = left + (MARIO_TAIL_BBOX_WIDTH + 10.0f)-3.0f;
				bottom = top + MARIO_TAIL_BBOX_HEIGHT;
			}
			else
			{
				if (nx > 0)
				{
					left = (x - (MARIO_TAIL_BBOX_WIDTH) / 2) + 2.0f;
					top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
					right = left + (MARIO_TAIL_BBOX_WIDTH)-3.0f;
					bottom = top + MARIO_TAIL_BBOX_HEIGHT;
				}
				else
				{
					left = x - (MARIO_TAIL_BBOX_WIDTH) / 2;
					top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
					right = left + (MARIO_TAIL_BBOX_WIDTH)-2.0f;
					bottom = top + MARIO_TAIL_BBOX_HEIGHT;
				}
			}
		}
	}
	else if (level == MARIO_LEVEL_BIG)
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
			left = x - (MARIO_BIG_BBOX_WIDTH - 4) / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + (MARIO_BIG_BBOX_WIDTH - 4);
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
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
	if (l == 3 && level != 3)
	{
		Tail = new CTail(x, y);
		CPlayScene::objects.push_back(Tail);
	}
	level = l;
}

void DeLevel(CMario* a)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (a->level == MARIO_LEVEL_TAIL)
	{
		a->level = MARIO_LEVEL_BIG;
		a->StartUntouchable();
		a->Tail->Delete();
	}
	else if (a->level == MARIO_LEVEL_BIG)
	{
		a->level = MARIO_LEVEL_SMALL;
		a->StartUntouchable();
	}
	else
	{
		a->SetState(MARIO_STATE_DIE);
		CPlayScene::turn -= 1;
		a->die_start = GetTickCount64();
	}
	a->setIsDelevel(true);
	a->setTimeSwitching(GetTickCount64());
}
void KickKoopas(CKoopas* Koopas, CMario* mario)
{
	if (Koopas->GetState() == KOOPAS_STATE_IS_HOLD_DOWN || Koopas->GetState() == KOOPAS_STATE_RETURN_DOWN)
		Koopas->SetState(KOOPAS_STATE_DIE_DOWN_SPIN);
	else if (Koopas->GetState() == KOOPAS_STATE_IS_HOLD_UP || Koopas->GetState() == KOOPAS_STATE_RETURN_UP)
		Koopas->SetState(KOOPAS_STATE_DIE_UP_SPIN);

	if (mario->getx() < Koopas->getx())
		Koopas->setVx(abs(KOOPAS_SPINNING_SPEED));
	else
		Koopas->setVx(-abs(KOOPAS_SPINNING_SPEED));

	Koopas = NULL;
}



