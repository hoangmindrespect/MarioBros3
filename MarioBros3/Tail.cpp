#include "Tail.h"
#include "Platform.h"
#include "debug.h"
#include "RedGoomba.h"
#include "Textures.h"
#include "PlayScene.h"
CTail::CTail(float x, float y) :CGameObject(x, y)
{
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
}

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	/*CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (mario->getIsAttack())
	{
		goomba->SetState(GOOMBA_STATE_DIE_BY_KOOPAS);
	}*/
}

void CTail::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	/*CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (mario->getIsAttack())
	{
		goomba->SetState(GOOMBA_STATE_DIE_BY_KOOPAS);
		goomba->Delete();
	}*/
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	if (mario->getnx() > 0)
	{
		x = mario->getx() + 10.0f;
		y = mario->gety() + 6.0f;
	}
	else
	{
		x = mario->getx() - 10.0f;
		y = mario->gety() + 6.0f;
	}
	
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
