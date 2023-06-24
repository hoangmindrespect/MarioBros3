#include "HUD.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"

CHUD* CHUD::__instance = NULL;
float CHUD::initialX = 0.0f; // Giá trị mặc định cho X
float CHUD::initialY = 0.0f; // Giá trị mặc định cho Y

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
	float cx, cy;
	CPlayScene::player->GetPosition(cx, cy);
	cx -= game->GetBackBufferWidth() / 2;
	if (cx < 0)
		x = HUD_WIDTH / 2;
	else
		x = cx + HUD_WIDTH / 2;
	
	CGameObject::Update(dt, coObjects);
}

void CHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 24.0f;
	t = y - 24.0f;
	r = l + 24.0f * 10;
	b = t + 24.0f;
}

CHUD* CHUD::GetInstance()
{
	if (__instance == NULL) __instance = new CHUD(initialX, initialY);
	return __instance;
}