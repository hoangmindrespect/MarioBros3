#include "Tail.h"
#include "Platform.h"
#include "debug.h"
#include "RedGoomba.h"
#include "Textures.h"
#include "PlayScene.h"
#include "PiranhaPlant.h"
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
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (mario->getIsAttack())
	{
		CEffect* a = new CEffect(goomba->getx(), goomba->gety(), 8);
		CEffect * b = new CEffect(goomba->getx(), goomba->gety(), 9);
		CPlayScene::objects.push_back(a);
		CPlayScene::objects.push_back(b);
		goomba->Delete();
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
	}
}

void CTail::OnCollisionWithRedGoomba(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CRedGoomba* goomba = dynamic_cast<CRedGoomba*>(e->obj);
	if (mario->getIsAttack())
	{
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
	if (mario->getIsAttack())
	{
		CEffect* a = new CEffect(koopas->getx(), koopas->gety(), 8);
		CPlayScene::objects.push_back(a);
		koopas->SetState(KOOPAS_STATE_DIE_UP);
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
	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, 0.4f);
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
}
