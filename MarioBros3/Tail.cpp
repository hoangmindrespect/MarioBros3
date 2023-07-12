#include "Tail.h"
#include "Platform.h"
#include "debug.h"
#include "RedGoomba.h"
#include "Textures.h"
#include "PlayScene.h"
#include "PiranhaPlant.h"
#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PSwitch.h"
CTail::CTail(float x, float y) :CGameObject(x, y)
{
	ax = 0.0F;
	ay = 0.0F;
}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	if (dynamic_cast<CRedGoomba*>(e->obj))
		OnCollisionWithRedGoomba(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (!CPlayScene::IsIntroScene())
	{
		if (mario->getIsAttack())
		{
			CEffect* a = new CEffect(goomba->getx(), goomba->gety(), 8);
			CEffect* b = new CEffect(goomba->getx(), goomba->gety(), 9);
			CPlayScene::objects.push_back(a);
			CPlayScene::objects.push_back(b);
			goomba->Delete();
		}
	}
}

void CTail::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CPiranhaPlant* pira = dynamic_cast<CPiranhaPlant*>(e->obj);
	if (mario->getIsAttack())
	{
		CEffect* a = new CEffect(pira->getx(), pira->gety() + 3.0f, 8);
		CPlayScene::objects.push_back(a);
		pira->Delete();
		CPlayScene::point += 100;
	}
}

void CTail::OnCollisionWithRedGoomba(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CRedGoomba* goomba = dynamic_cast<CRedGoomba*>(e->obj);
	if (mario->getIsAttack())
	{
		CPlayScene::point += 100;
		CEffect* a = new CEffect(goomba->getx(), goomba->gety(), 8);
		CEffect* b = new CEffect(goomba->getx(), goomba->gety(), 10);
		CPlayScene::objects.push_back(a);
		CPlayScene::objects.push_back(b);
		goomba->Delete();
	}
}

void CTail::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if (!CPlayScene::IsIntroScene() && mario->getIsAttack())
	{
		CEffect* a = new CEffect(koopas->getx(), koopas->gety(), 8);
		CPlayScene::objects.push_back(a);
		koopas->SetState(KOOPAS_STATE_DIE_UP);
	}
}

void CTail::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (mario->getIsAttack())
	{
		if (brick->getModel() == 2)
		{
			CEffect* a = new CEffect(brick->getx() + 8, brick->gety() - 8, 1);
			CEffect* b = new CEffect(brick->getx() + 8, brick->gety() - 8, 2);
			CEffect* c = new CEffect(brick->getx() + 8, brick->gety() - 8, 3);
			CEffect* d = new CEffect(brick->getx() + 8, brick->gety() - 8, 4);
			scene->AddObject(a);
			scene->AddObject(b);
			scene->AddObject(c); scene->AddObject(d);
			e->obj->Delete();
		}
	}
}

void CTail::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CQuestionBlock* p = dynamic_cast<CQuestionBlock*>(e->obj);
	if (mario->getIsAttack())
	{
		if (p->GetState() == QUESTIONBLOCK_STATE_NONE_EMPTY)
		{
			p->SetState(QUESTIONBLOCK_STATE_EMPTY);

			if (p->getType() == 1)
			{
				CCoin* t = new CCoin(p->getx(), p->gety() - 15.0f, 1);
				scene->AddObject(t);
				CPlayScene::coin += 1;
				CPlayScene::point += 100;
			}
			else if (p->getType() == 2) // question block contains item
			{
				if (mario->getlevel() == MARIO_LEVEL_SMALL)
				{
					CRedMushroom* mushroom = new CRedMushroom(p->getx(), p->gety(), 1);
					scene->AddObject1(mushroom);
				}
				else  if (mario->getlevel() == MARIO_LEVEL_BIG || mario->getlevel() == MARIO_LEVEL_TAIL)
				{
					CLeaf* leaf = new CLeaf(p->getx(), p->gety() - 55.0f);
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

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = ax * dt;
	vy = ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::Render()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX2);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, BBOX_ALPHA);
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
}
