#include "ColorBox.h"
#include "Platform.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "debug.h"
#include "Mario.h"

void CColorBox::RenderBoundingBox()
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

	float xx = x - this->width / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA1, rect.right - 1, rect.bottom - 1);
}

void CColorBox::Render()
{
	RenderBoundingBox();
}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2;
	t = y - 10.0f;
	r = l + this->width;
	b = t + 10.0f;
}
