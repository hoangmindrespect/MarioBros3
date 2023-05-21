#include "HUD.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"
void CHUD::RenderBoundingBox()
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

	float xx = x - 24.0f/ 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CHUD::Render()
{
	
	CSprites* s = CSprites::GetInstance();
	s->Get(164011)->Draw(x, y);

	RenderBoundingBox();
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	/*float cx, cy;
	CPlayScene::player->GetPosition(cx, cy);
	cx -= game->GetBackBufferWidth() / 2;
	if (CPlayScene::player->getx() > 190.0f)
		x = cx + 120.0f;
	else
		x = cx + 150.0f;*/

	//RECT clientRect;
	//GetClientRect(CGame::GetInstance()->getWnd(), &clientRect);

	//// Chuyển đổi tọa độ của cửa sổ game thành tọa độ màn hình
	//POINT clientTopLeft = { clientRect.left, clientRect.top };
	//ClientToScreen(CGame::GetInstance()->getWnd(), &clientTopLeft);

	//float leftEdge = clientTopLeft.x;
	//DebugOut(L"%f \n", leftEdge);
	CGameObject::Update(dt, coObjects);
}

void CHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 24.0f;
	t = y - 24.0f;
	r = l + 24.0f * 10;
	b = t + 24.0f;
}