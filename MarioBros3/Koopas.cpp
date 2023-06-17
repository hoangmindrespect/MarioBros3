#include "Koopas.h"
#include"ColorBox.h"
#include "Goomba.h"
#include "debug.h"
#include "Platform.h"
#include "QuestionBlock.h"
#include "PlayScene.h"
#include "RedMushroom.h"
#include "Leaf.h"
#include "Brick.h"
#include "Effect.h"
CKoopas::CKoopas(float x, float y, int color) :CGameObject(x, y)
{
	this->color = color;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	n = 1;
	this->vx = KOOPAS_WALKING_SPEED;
	SetState(KOOPAS_STATE_WALKING_RIGHT);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_DIE_DOWN_SPIN || state == KOOPAS_STATE_DIE_UP_SPIN || state == KOOPAS_STATE_DIE_UP	)
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
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (dynamic_cast<CKoopas*>(e->obj)) return;
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		if (state != KOOPAS_STATE_DIE_DOWN_SPIN && state != KOOPAS_STATE_DIE_UP_SPIN)
			return;
		else
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			if (goomba->GetState() != GOOMBA_STATE_DIE_BY_KOOPAS)
			{
				goomba->SetState(GOOMBA_STATE_DIE_BY_KOOPAS);
			}
		}
	}
	else if (dynamic_cast<CBrick*>(e->obj))
	{
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
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
	{
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
					CCoin* t = new CCoin(p->getx(), p->gety() - 25.0f, 1);
					scene->AddObject(t);
				}
				else if (p->getType() == 2)
				{
					CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
					if (mario->getlevel() == MARIO_LEVEL_SMALL)
					{
						CRedMushroom* mushroom = new CRedMushroom(p->getx(), p->gety());
						scene->AddObject1(mushroom);
					}
					else  if (mario->getlevel() == MARIO_LEVEL_BIG || mario->getlevel() == MARIO_LEVEL_TAIL)
					{
						CLeaf* leaf = new CLeaf(p->getx(), p->gety() - 45.0f);
						scene->AddObject(leaf);
					}
				}

			}
		}
	}
	else if (dynamic_cast<CPlatform*>(e->obj))
	{
		CPlatform* plat = dynamic_cast<CPlatform*>(e->obj);
		if (plat->IsBlocking() == 0)
		{
			if (plat->getIsBlockKoopas() == 0)
			{
				if (e->ny < 0) {
					SetYWhenCollideColorbox(plat);
				}
			}
			else
			{
				if (state == KOOPAS_STATE_WALKING_RIGHT || state == KOOPAS_STATE_WALKING_LEFT)
				{
					vx = -vx;
					n = -n;
					if (n < 0 && state == KOOPAS_STATE_WALKING_RIGHT)
						SetState(KOOPAS_STATE_WALKING_LEFT);
					if (n > 0 && state == KOOPAS_STATE_WALKING_LEFT)
						SetState(KOOPAS_STATE_WALKING_RIGHT);
				}
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
		n = -n;
		if (n < 0 && state == KOOPAS_STATE_WALKING_RIGHT)
			SetState(KOOPAS_STATE_WALKING_LEFT);
		if (n > 0 && state == KOOPAS_STATE_WALKING_LEFT)
			SetState(KOOPAS_STATE_WALKING_RIGHT);
	}
}
void CKoopas::SetYWhenCollideColorbox(LPGAMEOBJECT gameobject) {
	
	if (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)
	{
		if (gameobject->gety() - gety() < KOOPAS_BBOX_HEIGHT)
		{
			sety(gameobject->gety() - KOOPAS_BBOX_HEIGHT + 4.0f);
			vy = 0;
		}
	}
	else
	{
		if (gameobject->gety() - gety() < KOOPAS_BBOX_HEIGHT_DIE)
		{
			sety(gameobject->gety() - KOOPAS_BBOX_HEIGHT_DIE - 1.0f);
			vy = 0;
		}
	}
}
void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_IS_HOLD_DOWN || state == KOOPAS_STATE_IS_HOLD_UP || state == KOOPAS_STATE_DIE_UP)
	{
		if (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT)
		{
			if(state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_IS_HOLD_DOWN)
				SetState(KOOPAS_STATE_RETURN_DOWN);
			else
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
			if (n > 0)
				SetState(KOOPAS_STATE_WALKING_RIGHT);
			else
				SetState(KOOPAS_STATE_WALKING_LEFT);
			y -= 18;
			ay = KOOPAS_GRAVITY;
			
		}
		else
		{
			if (!shaking)
			{
				x -= 1; shaking = true;
			}
			else
			{
				x += 1; shaking = false;
			}
		}
	}
	
	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	if (color == 1)
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
	else if (color == 2)
	{
		int aniId = ID_ANI_GREEN_KOOPAS_WALKING_RIGHT;
		if (state == KOOPAS_STATE_WALKING_RIGHT)
			aniId = ID_ANI_GREEN_KOOPAS_WALKING_RIGHT;
		else if (state == KOOPAS_STATE_WALKING_LEFT)
			aniId = ID_ANI_GREEN_KOOPAS_WALKING_LEFT;
		else if (state == KOOPAS_STATE_DIE_DOWN || state == KOOPAS_STATE_IS_HOLD_DOWN)
			aniId = ID_ANI_GREEN_KOOPAS_DIE_DOWN;
		else if (state == KOOPAS_STATE_DIE_DOWN_SPIN)
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
		y += 6;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPAS_STATE_DIE_UP:
	{
		CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
		if (mario->getIsAttack())
		{
			die_start = GetTickCount64();
			vx = 0;
			vy = -0.3f;
			ay = KOOPAS_GRAVITY;
		}
		else
		{
			die_start = GetTickCount64();
			y += 6;
			vx = 0;
			vy = 0;
			ay = 0;
		}
		
		break;
	}
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		n = 1;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		n = -1;
		break;
	case KOOPAS_STATE_DIE_DOWN_SPIN:
		ay = KOOPAS_GRAVITY;
	case KOOPAS_STATE_DIE_UP_SPIN:
		ay = KOOPAS_GRAVITY;
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
	}

}
