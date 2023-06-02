#include "MarioStop.h"
#include "Platform.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"

void CMarioStop::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, 0.5);
}

void CMarioStop::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteID)->Draw(x, y);

	RenderBoundingBox();
}

void CMarioStop::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 8.0f;
	t = y - 8.0f;
	r = l + 16.0f;
	b = t + 16.0f;
}