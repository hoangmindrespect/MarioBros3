#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(model == 1)
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	else if(model == 2)
		animations->Get(ID_ANI_BRICK1)->Render(x, y);
	else if(model == 3)
		animations->Get(ID_ANI_BRICK2)->Render(x, y);

	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}