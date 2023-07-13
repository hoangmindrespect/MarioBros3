#include "Koopas.h"
#include"ColorBox.h"
#include "Goomba.h"
#include "debug.h"
#include "Platform.h"
#include "QuestionBlock.h"
#include "PlayScene.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Brick.h"
#include "Effect.h"
#include "PSwitch.h"
#include "PiranhaPlant.h"
#include "RedGoomba.h"
CKoopas::CKoopas(float x, float y, int type) : CGameObject(x, y)
{
	this->type = type;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;

	if(type == 1 || type  == 2)
	{
		SetState(KOOPAS_STATE_WALKING_LEFT);
	}
	else
	{
		isJumping = false;
		SetState(JUMP_KOOPAS_STATE_JUMPING);
		nx = -1;
		this->vx = -KOOPAS_WALKING_SPEED;
		jumping_start = GetTickCount64();
	}
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_DIE_DOWN_SPIN || state == KOOPAS_STATE_DIE_UP_SPIN || state == KOOPAS_STATE_DIE_UP	|| state == KOOPAS_STATE_IS_HOLD_UP || state == KOOPAS_STATE_IS_HOLD_DOWN || state == KOOPAS_STATE_RETURN_DOWN || state == KOOPAS_STATE_RETURN_UP || state == KOOPAS_STATE_FALL_INTO_MARIO)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (dynamic_cast<CKoopas*>(e->obj)) {
		CKoopas* des = dynamic_cast<CKoopas*>(e->obj);
		float des_x = 0.0f, des_y = 0.0f;
		des->GetPosition(des_x, des_y);
		if (CPlayScene::IsIntroScene())
		{
			if (des->type == 4)
			{
				e->obj->Delete();

				CEffect* a = new CEffect(des_x, des_y - 2.0f, 12);
				CPlayScene::objects.push_back(a);
				return;
			}
		}
		else if (state == KOOPAS_STATE_DIE_DOWN_SPIN || state == KOOPAS_STATE_DIE_UP_SPIN)
		{
			CEffect* a = new CEffect(des_x, des_y, 13);
			CPlayScene::objects.push_back(a);

			CEffect* b = new CEffect(des_x, des_y, 6);
			CPlayScene::objects.push_back(b);

			CEffect*c = new CEffect(des_x, des_y, 8);
			CPlayScene::objects.push_back(c);

			e->obj->SetPosition(9999999.0f, 9999999.0f);
		}
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomBa(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CRedGoomba*>(e->obj))
		OnCollisionWithRedGoomBa(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
	{
		CPlatform* plat = dynamic_cast<CPlatform*>(e->obj);
		if (plat->IsBlocking() == 0)
		{
			if (state == KOOPAS_STATE_WALKING_RIGHT || state == KOOPAS_STATE_WALKING_LEFT)
			{
				vx = -vx;
				nx = -nx;
				if (nx < 0 && state == KOOPAS_STATE_WALKING_RIGHT)
					SetState(KOOPAS_STATE_WALKING_LEFT);
				if (nx > 0 && state == KOOPAS_STATE_WALKING_LEFT)
					SetState(KOOPAS_STATE_WALKING_RIGHT);
			}
		}
		else
		{
			if (state == KOOPAS_STATE_FALL_INTO_MARIO)
			{
				vx = vy = 0;
				SetState(KOOPAS_STATE_DIE_DOWN);
			}
		}
	}
	

	if (e->obj->IsBlocking() == 0)
		return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
		if (nx < 0 && state == KOOPAS_STATE_WALKING_RIGHT)
			SetState(KOOPAS_STATE_WALKING_LEFT);
		if (nx > 0 && state == KOOPAS_STATE_WALKING_LEFT)
			SetState(KOOPAS_STATE_WALKING_RIGHT);
	}
}
void CKoopas::OnCollisionWithRedGoomBa(LPCOLLISIONEVENT e)
{
	CRedGoomba* red = dynamic_cast<CRedGoomba*>(e->obj);
	if (state == KOOPAS_STATE_DIE_DOWN_SPIN || state == KOOPAS_STATE_DIE_UP_SPIN)
	{
		CPlayScene::point += 100;

		CEffect* a = new CEffect(red->getx(), red->gety(), 10);
		CPlayScene::objects.push_back(a);

		CEffect* b = new CEffect(red->getx(), red->gety(), 6);
		CPlayScene::objects.push_back(b);

		CEffect* c = new CEffect(red->getx(), red->gety(), 8);
		CPlayScene::objects.push_back(c);

		e->obj->Delete();
	}
}

void CKoopas::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* pi = dynamic_cast<CPiranhaPlant*>(e->obj);
	if (state == KOOPAS_STATE_DIE_DOWN_SPIN || state == KOOPAS_STATE_DIE_UP_SPIN)
	{
		if (!pi->IsCannotBeAttack())
		{
			CPlayScene::point += 100;
			CEffect* e = new CEffect(pi->getx(), pi->gety(), 8);
			CEffect* p = new CEffect(pi->getx(), pi->gety(), 6);
			CPlayScene::objects.push_back(e);
			CPlayScene::objects.push_back(p);
			pi->Delete();
		}
	}
}

void CKoopas::OnCollisionWithGoomBa(LPCOLLISIONEVENT e)
{
	if (state != KOOPAS_STATE_DIE_DOWN_SPIN && state != KOOPAS_STATE_DIE_UP_SPIN)
		return;
	else
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		if (goomba->GetState() != GOOMBA_STATE_DIE_BY_KOOPAS)
		{
			CPlayScene::point += 100;
			CEffect* a = new CEffect(goomba->getx(), goomba->gety(), 8);
			CEffect* b = new CEffect(goomba->getx(), goomba->gety(), 9);
			CEffect* c = new CEffect(goomba->getx(), goomba->gety(), 6);
			CPlayScene::objects.push_back(a);
			CPlayScene::objects.push_back(b);
			CPlayScene::objects.push_back(c);

			goomba->Delete();
		}
	}
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CBrick* b = dynamic_cast<CBrick*>(e->obj);
	if (e->nx != 0)
	{
		if (state == KOOPAS_STATE_DIE_DOWN_SPIN || state == KOOPAS_STATE_DIE_UP_SPIN)
		{

			if (b->getModel() == 2)
			{
				CEffect* a = new CEffect(e->obj->getx() + 8, e->obj->gety() - 8, 1);
				CEffect* b = new CEffect(e->obj->getx() + 8, e->obj->gety() - 8, 2);
				CEffect* c = new CEffect(e->obj->getx() + 8, e->obj->gety() - 8, 3);
				CEffect* d = new CEffect(e->obj->getx() + 8, e->obj->gety() - 8, 4);
				scene->AddObject(a);
				scene->AddObject(b);
				scene->AddObject(c); scene->AddObject(d);
				e->obj->Delete();
			}
		}
	}
}

void CKoopas::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (state != KOOPAS_STATE_DIE_DOWN_SPIN && state != KOOPAS_STATE_DIE_UP_SPIN)
		return;
	else
	{
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CQuestionBlock* p = dynamic_cast<CQuestionBlock*>(e->obj);
		if (e->nx != 0 && p->GetState() == QUESTIONBLOCK_STATE_NONE_EMPTY)
		{
			p->SetState(QUESTIONBLOCK_STATE_EMPTY);

			if (p->getType() == 1)
			{
				CPlayScene::coin += 1;
				CCoin* t = new CCoin(p->getx(), p->gety() - 25.0f, 1);
				scene->AddObject(t);
			}
			else if (p->getType() == 2)
			{
				CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
				if (mario->getlevel() == MARIO_LEVEL_SMALL)
				{
					CRedMushroom* mushroom = new CRedMushroom(p->getx(), p->gety(), 1);
					scene->AddObject1(mushroom);
				}
				else  if (mario->getlevel() == MARIO_LEVEL_BIG || mario->getlevel() == MARIO_LEVEL_TAIL)
				{
					CLeaf* leaf = new CLeaf(p->getx(), p->gety() - 45.0f);
					scene->AddObject(leaf);
				}
			}
			else if (p->getType() == 3)
			{
				CPSwitch* pswitch = new CPSwitch(p->getx(), p->gety() - 16.0f);
				scene->AddObject(pswitch);
			}
			else if (p->getType() == 4)
			{
				CRedMushroom* mushroom = new CRedMushroom(p->getx(), p->gety(), 2);
				scene->AddObject1(mushroom);
			}
		}
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	if (state == JUMP_KOOPAS_STATE_JUMPING)
	{
		if (GetTickCount64() - jumping_start > 800)
		{
			SetState(JUMP_KOOPAS_STATE_JUMPING);
			jumping_start = GetTickCount64();
		}
	}

	if (state == KOOPAS_STATE_IS_HOLD_DOWN || state == KOOPAS_STATE_IS_HOLD_UP || state == KOOPAS_STATE_RETURN_DOWN || state == KOOPAS_STATE_RETURN_UP)
	{
		if (mario != NULL && mario->getIsHolding()) {

			float mx = mario->getx();
			float my = mario->gety();
			vx = vy = 0;
			if (mario->getlevel() == MARIO_LEVEL_TAIL)
			{
				if (mario->getnx() > 0)
				{
					x = mx + 15.0f;
					y = my + 2.0f;
				}
				else
				{
					x = mx - 15.0f;
					y = my + 2.0f;
				}
			}
			else if (mario->getlevel() == MARIO_LEVEL_BIG)
			{
				if (mario->getnx() > 0)
				{
					x = mx + 10.0f;
					y = my + 2.0f;
				}
				else
				{
					x = mx - 10.0f;
					y = my + 2.0f;
				}
			}
			else
			{
				if (mario->getnx() > 0)
				{
					x = mx + 7.0f;
					y = my - 3.0f;
				}
				else
				{
					x = mx - 7.0f;
					y = my - 3.0f;
				}
			}
		}
	}	

	if (CPlayScene::IsIntroScene())
	{
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}

	if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_IS_HOLD_DOWN || state == KOOPAS_STATE_IS_HOLD_UP || state == KOOPAS_STATE_DIE_UP)
	{
		if (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT)
		{
			if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_IS_HOLD_DOWN)
			{
				SetState(KOOPAS_STATE_RETURN_DOWN);
			}
			else if(state == KOOPAS_STATE_DIE_UP || state == KOOPAS_STATE_IS_HOLD_UP)
			{
				SetState(KOOPAS_STATE_RETURN_UP);
			}
			return_start = GetTickCount64();
		}
	}

	if (state == KOOPAS_STATE_RETURN_DOWN || state == KOOPAS_STATE_RETURN_UP)
	{
		if (GetTickCount64() - return_start > 2000)
		{
			if (nx > 0)
				SetState(KOOPAS_STATE_WALKING_RIGHT);
			else
				SetState(KOOPAS_STATE_WALKING_LEFT);
			y -= 10;
			ay = KOOPAS_GRAVITY;
			
		}
		else
		{
			if (!shaking)
			{
				x -= 0.8f; shaking = true;
			}
			else
			{
				x += 0.8f; shaking = false;
			}
		}
	}	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	if (type == 1)
	{
		int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
		if (state == KOOPAS_STATE_WALKING_RIGHT)
			aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
		else if (state == KOOPAS_STATE_WALKING_LEFT)
			aniId = ID_ANI_KOOPAS_WALKING_LEFT;
		else if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_IS_HOLD_DOWN)
			aniId = ID_ANI_KOOPAS_DIE_DOWN;
		else if (state == KOOPAS_STATE_DIE_DOWN_SPIN)
			aniId = ID_ANI_KOOPAS_DIE_DOWN_SPIN;
		else if (state == KOOPAS_STATE_DIE_UP || state == KOOPAS_STATE_IS_HOLD_UP)
			aniId = ID_ANI_KOOPAS_DIE_UP;
		else if (state == KOOPAS_STATE_DIE_UP_SPIN)
			aniId = ID_ANI_KOOPAS_DIE_UP_SPIN;
		else if (state == KOOPAS_STATE_RETURN_DOWN)
			aniId = ID_ANI_KOOPAS_RETURN_DOWN;
		else if (state == KOOPAS_STATE_RETURN_UP)
			aniId = ID_ANI_KOOPAS_RETURN_UP;
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	else if (type == 2 || type == 3 || type == 4)
	{
		int aniId = ID_ANI_GREEN_KOOPAS_WALKING_RIGHT;
		if (state == JUMP_KOOPAS_STATE_JUMPING)
		{
			if (nx > 0)
				aniId = ID_ANI_GREEN_KOOPAS_MOVING_RIGHT;
			else
				aniId = ID_ANI_GREEN_KOOPAS_MOVING_LEFT;
		}
		else if (state == KOOPAS_STATE_WALKING_RIGHT)
			aniId = ID_ANI_GREEN_KOOPAS_WALKING_RIGHT;
		else if (state == KOOPAS_STATE_WALKING_LEFT)
			aniId = ID_ANI_GREEN_KOOPAS_WALKING_LEFT;
		else if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_IS_HOLD_DOWN)
		{
			if(type == 4)
				aniId = ID_ANI_BLACK_KOOPAS_DIE_DOWN;
			else
				aniId = ID_ANI_GREEN_KOOPAS_DIE_DOWN;
		}
		else if (state == KOOPAS_STATE_DIE_DOWN_SPIN || state == KOOPAS_STATE_FALL_INTO_MARIO) // INTRO SCENE
			aniId = ID_ANI_GREEN_KOOPAS_DIE_DOWN_SPIN;
		else if (state == KOOPAS_STATE_DIE_UP || state == KOOPAS_STATE_IS_HOLD_UP)
			aniId = ID_ANI_GREEN_KOOPAS_DIE_UP;
		else if (state == KOOPAS_STATE_DIE_UP_SPIN)
			aniId = ID_ANI_GREEN_KOOPAS_DIE_UP_SPIN;
		else if (state == KOOPAS_STATE_RETURN_DOWN)
			aniId = ID_ANI_GREEN_KOOPAS_RETURN_DOWN;
		else if (state == KOOPAS_STATE_RETURN_UP)
			aniId = ID_ANI_GREEN_KOOPAS_RETURN_UP;

		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE_DOWN:
		die_start = GetTickCount64();
		y += 3;
		vx = 0;
		vy = 0;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_DIE_UP:
	{
		CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
		if (mario->getIsAttack())
		{
			die_start = GetTickCount64();
			vx = 0.0f;
			vy = -0.3f;
			ay = KOOPAS_GRAVITY;
		}
		else
		{
			die_start = GetTickCount64();
			y += 6;
			vx = 0;
			ay = KOOPAS_GRAVITY;
		}
		break;
	}
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		nx = 1;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPAS_STATE_DIE_DOWN_SPIN:
		ay = KOOPAS_GRAVITY;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE_UP_SPIN:
		ay = KOOPAS_GRAVITY;
		vy = 0;
		break;
	case KOOPAS_STATE_IS_HOLD_DOWN:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_IS_HOLD_UP:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPAS_STATE_RETURN_UP:
		ay = 0;
		vy = 0;
		break;
	case JUMP_KOOPAS_STATE_JUMPING:
		ay = KOOPAS_GRAVITY;
		vy = -0.26f;
		break;
	case KOOPAS_STATE_FALL_INTO_MARIO:
		ay = KOOPAS_GRAVITY;
		vy = 0.03f;
		vx = -0.05f;
		break;
	}
	
}
