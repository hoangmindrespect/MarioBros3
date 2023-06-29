#include "TurnInHUD.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"

void CTurnInHUD::RenderBoundingBox()
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

	float xx = x - TURNINHUD_WIDTH / 2 + rect.right / 2;
	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CTurnInHUD::Render()
{
	CSprites* s = CSprites::GetInstance();
	int game_turn = CPlayScene::turn;

	// just hanlde max 9 turn
	switch (game_turn)
	{
	case 0:
		s->Get(ID_FONT_NUMBER_ZERO)->Draw(x , y); break;
	case 1:
		s->Get(ID_FONT_NUMBER_ONE)->Draw(x , y); break;
	case 2:
		s->Get(ID_FONT_NUMBER_TWO)->Draw(x , y); break;
	case 3:
		s->Get(ID_FONT_NUMBER_THREE)->Draw(x , y); break;
	case 4:
		s->Get(ID_FONT_NUMBER_FOUR)->Draw(x , y); break;
	case 5:
		s->Get(ID_FONT_NUMBER_FIVE)->Draw(x , y); break;
	case 6:
		s->Get(ID_FONT_NUMBER_SIX)->Draw(x , y); break;
	case 7:
		s->Get(ID_FONT_NUMBER_SEVEN)->Draw(x , y); break;
	case 8:
		s->Get(ID_FONT_NUMBER_EIGHT)->Draw(x , y); break;
	case 9:
		s->Get(ID_FONT_NUMBER_NINE)->Draw(x , y); break;
	default:
		break;
	}
	RenderBoundingBox();
}

void CTurnInHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGame* game = CGame::GetInstance();
	float cx, cy;
	mario->GetPosition(cx, cy);
	cx -= game->GetBackBufferWidth() / 2;
	if (cx < 0)
		x = TURNINHUD_X_DEFAULT;
	else
		x = cx + TURNINHUD_X_DEFAULT;
	if (cy > 200.0f)
		y = TURNINHUD_Y_HIDDEN;
	else y = TURNINHUD_Y_DEFAULT;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTurnInHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TURNINHUD_WIDTH / 2;
	t = y - TURNINHUD_HEIGHT / 2;
	r = l + TURNINHUD_WIDTH;
	b = t + TURNINHUD_HEIGHT;
}

