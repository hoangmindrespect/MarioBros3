#include "Leaf.h"

void CLeaf::Render()
{

	CSprites* s = CSprites::GetInstance();
	s->Get(idsprite)->Draw(x, y);

	RenderBoundingBox();
}
void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	if (IsUp == false && y > maxy)
		y -= 0.3f * dt;
	else
	{
		IsUp = true;
		if (IsRight == true && IsLeft == false)
		{
			if (x < rightmax)
			{
				x += 0.08f * dt;
				y += 0.05f * dt;
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
				x -= 0.08f * dt;
				y += 0.05f * dt;
			}
			else
			{
				IsRight = true;
				IsLeft = false;
			}

		}

	}
	CGameObject::Update(dt, coObjects);
		}
void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}