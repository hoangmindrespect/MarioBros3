#include "Effect.h"
#include "debug.h"
#include "PlayScene.h"
CEffect ::CEffect(float x, float y, int k) : CGameObject(x, y) {
	type = k;
	if (k == 1) // phải thấp
	{
		vx = 0.12f;
		vy = -0.4f;
		ax = 0;
		ay = 0.003f;
	}
	else if (k == 2) // phải cao
	{
		vx = 0.12f;
		vy = -0.55f;
		ax = 0;
		ay = 0.003f;
	}
	else if (k == 3) //trái thấp
	{
		vx = -0.12f;
		vy = -0.4f;
		ax = 0;
		ay = 0.003f;
	}
	else if (k == 4) // trái cao
	{
		vx = -0.12f;
		vy = -0.55f;
		ax = 0;
		ay = 0.003f;
	}
	else if (k == 5)
	{
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
	}
}

void CEffect::Render()
{
	int idAni = -1;
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	if(type == 1 || type == 2 || type == 3 || type == 4)
		idAni = 35201;
	else if (type == 5)
	{
		if (mario->getnx() > 0)
			idAni = 35202;
		else
			idAni = 35203;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(idAni)->Render(x, y);

	RenderBoundingBox();
}
void CEffect::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	
	vx += ax * dt;
	vy += ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}