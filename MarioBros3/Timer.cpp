#include "Timer.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"

void CTimer::RenderBoundingBox()
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

	float xx = x - TIMER_WIDTH / 2 + rect.right / 2;
	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CTimer::Render()
{
	CSprites* s = CSprites::GetInstance();
	ULONGLONG time_tmp = time;
	float distance = 0.0f;
	while (distance != 24.0f)
	{
		switch (time_tmp % 10)
		{
		case 0:
			s->Get(ID_FONT_NUMBER_ZERO)->Draw(x + 16.0f - distance, y); break;
		case 1:
			s->Get(ID_FONT_NUMBER_ONE)->Draw(x + 16.0f - distance, y); break;
		case 2:
			s->Get(ID_FONT_NUMBER_TWO)->Draw(x + 16.0f - distance, y); break;
		case 3:
			s->Get(ID_FONT_NUMBER_THREE)->Draw(x + 16.0f - distance, y); break;
		case 4:
			s->Get(ID_FONT_NUMBER_FOUR)->Draw(x + 16.0f - distance, y); break;
		case 5:
			s->Get(ID_FONT_NUMBER_FIVE)->Draw(x + 16.0f - distance, y); break;
		case 6:
			s->Get(ID_FONT_NUMBER_SIX)->Draw(x + 16.0f - distance, y); break;
		case 7:
			s->Get(ID_FONT_NUMBER_SEVEN)->Draw(x + 16.0f - distance, y); break;
		case 8:
			s->Get(ID_FONT_NUMBER_EIGHT)->Draw(x + 16.0f - distance, y); break;
		case 9:
			s->Get(ID_FONT_NUMBER_NINE)->Draw(x + 16.0f - distance, y); break;
		default:
			break;
		}
		time_tmp = time_tmp / 10;
		distance += 8.0f;
	}
	RenderBoundingBox();
}

void CTimer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (time <= 0)
	{
		//mario->setDieStart();
		mario->SetState(MARIO_STATE_DIE);
	}
	time = 300.0f - (GetTickCount64() / 1000.0f - start);
	CGame* game = CGame::GetInstance();
	float cx, cy;
	mario->GetPosition(cx, cy);
	cx -= game->GetBackBufferWidth() / 2;
	if (cx < 0)
		x = TIMER_X_DEFAULT;
	else
		x = cx + TIMER_X_DEFAULT;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTimer::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TIMER_WIDTH / 2;
	t = y - TIMER_HEIGHT / 2;
	r = l + TIMER_WIDTH;
	b = t + TIMER_HEIGHT;
}

