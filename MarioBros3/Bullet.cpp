#include "Bullet.h"

void CBullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BULLET)->Render(x, y);

	RenderBoundingBox();
}
void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	x += vx * dt;
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
}
void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLET_BBOX_WIDTH / 2;
	t = y - BULLET_BBOX_HEIGHT / 2;
	r = l + BULLET_BBOX_WIDTH;
	b = t + BULLET_BBOX_HEIGHT;
}