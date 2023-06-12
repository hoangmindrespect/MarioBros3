#include "Curtains.h"
#include "debug.h"
#include "GrassInMap.h"
void CCurtains::Render()
{
	if (!isUp)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(166036)->Draw(x, y);
	}
	else 
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(166038)->Draw(x, y);
	}

	if (intoAni)
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(166039)->Draw(x, y);
		s->Get(166044)->Draw(x, y + 63);

		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(45431)->Render(x + 5, y + 25);
	}

	RenderBoundingBox();
}
void CCurtains::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	
	if(y > -88 && !isUp)
	{
		y -= 0.07 * dt; 
	}
	else if(y < 94 && !isDown)
	{
		isUp = true;
		y += 0.2 * dt;
	}
	else
	{
		if(!isDown)
			time_shaking = GetTickCount64();
		isDown = true;
		
	}

	if (isUp && isDown)
	{
		if (GetTickCount64() - time_shaking <= 1000)
		{
			if (!flag)
			{
				y -= 1; flag = true;
			}
			else
			{
				y += 1; flag = false;
			}

		}
		else
			intoAni = true;
	}
	CGameObject::Update(dt, coObjects);
}
void CCurtains::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 255 / 2;
	t = y - 184 / 2;
	r = l + 255;
	b = t + 184;
}