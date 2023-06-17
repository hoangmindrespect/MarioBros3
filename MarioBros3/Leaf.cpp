#include "Leaf.h"
#include "Mario.h"

void CLeaf::Render()
{

	CSprites* s = CSprites::GetInstance();
	if (nx > 0)
	{
		s->Get(ID_ANI_LEAF_RIGHT)->Draw(x, y);
	}
	else
	{
		s->Get(ID_ANI_LEAF_LEFT)->Draw(x, y);
	}

	RenderBoundingBox();
}
void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {

	vx += ax * dt;
	vy += ay * dt;

	if (IsRight == true && IsLeft == false)
	{
		if (x < rightmax)
		{
			vx = 0.08f;
			vy = 0.03f;
			nx = -1;
		}
		else
		{
			IsRight = false;
			IsLeft = true;
		}

	}
	if (IsRight == false && IsLeft == true)
	{
		if (x > rightmin)
		{
			vx = -0.08f;
			vy = 0.03f;
			nx = 1;
		}
		else
		{
			IsRight = true;
			IsLeft = false;
		}

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}
void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}