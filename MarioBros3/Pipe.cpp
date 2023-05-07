#include "Pipe.h"
#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPipe::RenderBoundingBox()
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

	float yy = y - this->cellHeight / 2 + rect.right / 1.3;

	CGame::GetInstance()->Draw(x - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right, rect.bottom - 1);
}

void CPipe::Render()
{
	if (this->height <= 0) return;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdTop)->Draw(x, yy);
	yy += this->cellHeight ;
	for (int i = 1; i < this->height; i++)
	{
		s->Get(this->spriteIdBottom)->Draw(x, yy);
		yy += this->cellHeight;
	}

	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth;
	b = t + this->cellHeight * this->height;
}