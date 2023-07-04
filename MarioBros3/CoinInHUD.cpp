#include "CoinInHUD.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"

void CCoinInHUD::RenderBoundingBox()
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

	float xx = x - COININHUD_WIDTH / 2 + rect.right / 2;
	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CCoinInHUD::Render()
{
	CSprites* s = CSprites::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int coin = CPlayScene::coin;
	if (coin == 0)
	{
		s->Get(ID_FONT_NUMBER_ZERO)->Draw(x + 8.0f, y);
		return;
	}

	float distance = 0.0f;
	while (coin > 0)
	{
		switch (coin % 10)
		{
		case 0:
			s->Get(ID_FONT_NUMBER_ZERO)->Draw(x + 8.0f - distance, y); break;
		case 1:
			s->Get(ID_FONT_NUMBER_ONE)->Draw(x + 8.0f - distance, y); break;
		case 2:
			s->Get(ID_FONT_NUMBER_TWO)->Draw(x + 8.0f - distance, y); break;
		case 3:
			s->Get(ID_FONT_NUMBER_THREE)->Draw(x + 8.0f - distance, y); break;
		case 4:
			s->Get(ID_FONT_NUMBER_FOUR)->Draw(x + 8.0f - distance, y); break;
		case 5:
			s->Get(ID_FONT_NUMBER_FIVE)->Draw(x + 8.0f - distance, y); break;
		case 6:
			s->Get(ID_FONT_NUMBER_SIX)->Draw(x + 8.0f - distance, y); break;
		case 7:
			s->Get(ID_FONT_NUMBER_SEVEN)->Draw(x + 8.0f - distance, y); break;
		case 8:
			s->Get(ID_FONT_NUMBER_EIGHT)->Draw(x + 8.0f - distance, y); break;
		case 9:
			s->Get(ID_FONT_NUMBER_NINE)->Draw(x + 8.0f - distance, y); break;
		default:
			break;
		}
		coin = coin / 10;
		distance += 8.0f;
	}

	//RenderBoundingBox();
}

void CCoinInHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGame* game = CGame::GetInstance();
	float cx, cy;
	mario->GetPosition(cx, cy);
	cx -= game->GetBackBufferWidth() / 2;
	if (cx < 0)
		x = COININHUD_X_DEFAULT;
	else
		x = cx + COININHUD_X_DEFAULT;
	if (cy > 200.0f)
		y = COININHUD_Y_HIDDEN;
	else y = COININHUD_Y_DEFAULT;

	//in worldmap
	if (mario->getIsInMap())
		x = COININHUD_X_DEFAULT;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoinInHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COININHUD_WIDTH / 2;
	t = y - COININHUD_HEIGHT / 2;
	r = l + COININHUD_WIDTH;
	b = t + COININHUD_HEIGHT;
}

