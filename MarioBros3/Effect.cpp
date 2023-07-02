#include "Effect.h"
#include "debug.h"
#include "PlayScene.h"
CEffect ::CEffect(float x, float y, int k) : CGameObject(x, y) {
	type = k;
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	if (k == 1) // phải thấp
	{
		vx = 0.12f;
		vy = -0.4f;
		ax = 0;
		ay = 0.003f;
	}
	else if (k == 2 ) // phải cao
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
	else if (k == 5) // biến hình thành tail
	{
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
	}
	else if (type == 6 || type == 7 || type == 11) // + 100 point, + 1000 point, + 1 turn
	{
		top = y - 40.0f;
		vx = 0;
		vy = -0.1f;
		ax = 0;
		ay = 0;
	}
	else if (type == 8) // attack by tail or defend koopas
	{
		time_start = GetTickCount64();
		vx = vy = ax = ay = 0.0f;
	}
	else if (k == 9 || k == 10 || k == 12) // phải cao
	{
		if (mario != NULL)
		{
			if(mario->getnx() > 0)
				vx = 0.12f;
			else
				vx = -0.12f;
		}
		else
			vx = 0.12f;
		vy = -0.65f;
		ax = 0;
		ay = 0.003f;
	}
}

void CEffect::Render()
{
	int idAni = -1;
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	if(type == 1 || type == 2 || type == 3 || type == 4)
		idAni = ID_ANI_BROKE_BRICK;
	else if (type == 5)
	{
		if (mario->getnx() > 0)
			idAni = ID_ANI_SMALL_TO_BIG_RIGHT;
		else
			idAni = ID_ANI_SMALL_TO_BIG_LEFT;
	}
	else if (type == 6)
	{
		idAni = ID_ANI_POINT_PLUS_100;
	}
	else if (type == 7)
	{
		idAni = ID_ANI_POINT_PLUS_1000;
	}
	else if (type == 8)
	{
		idAni = ID_ANI_ATTACK;
	}
	else if (type == 9)
	{
		idAni = ID_YELLOW_GOOMBA_DIE_EFFECT;
	}
	else if (type == 10)
	{
		idAni = ID_RED_GOOMBA_DIE_EFFECT;
	}
	else if (type == 11)
	{
		idAni = ID_RED_ONE_UP;
	}
	else if (type == 12)
	{
		idAni = ID_ANI_BLACK_KOOPAS_DIE_UP;
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
	if (type == 6 || type == 7 || type == 11)
	{
		if (y < top)
			this->Delete();
	}
	else if (type == 8)
	{
		if (GetTickCount64() - time_start > 100)
		{
			this->Delete();
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}