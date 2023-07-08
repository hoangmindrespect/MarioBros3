#include "HUD.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"

//CHUD* CHUD::__instance = NULL;
//float CHUD::initialX = 0.0f; // Giá trị mặc định cho X
//float CHUD::initialY = 0.0f; // Giá trị mặc định cho Y

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

	float xx = x - HUD_WIDTH/ 2 + rect.right / 2;
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
	float mario_x, mario_y;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->GetPosition(cx, cy);
	mario->GetPosition(mario_x, mario_y);
	cx -= game->GetBackBufferWidth() / 2;

	if (cx < 0)
		x = HUD_WIDTH / 2;
	else
		x = cx + HUD_WIDTH / 2;

	float cy_tmp = cy - game->GetBackBufferHeight() / 2;
	if (mario_y < COORDINATES_ADJUST_CAMERA_FIRST)
	{
		if (mario->GetState() == MARIO_STATE_FLYING)
		{
			if (mario_y < COORDINATES_ADJUST_CAMERA_SECOND)
				y = -99.0f;
			else
				y = cy_tmp + 255.0f;
		}
		else
		{
			if (!mario->getIsOnPlatForm())
			{
				if (!mario->getIsFallDown())
				{
					if (mario_y < ON_CLOUD)
					{
						mario->setIsFallDown(true);
					}
				}
				else
				{
					if (mario_y > ON_CLOUD + 30.0f)
						mario->setIsFallDown(false);
				}

				if (mario->getIsFallDown())
				{
					if (mario_y < COORDINATES_ADJUST_CAMERA_SECOND)
						y = -99.0f;
					else
						y = cy_tmp + 233.0f;
				}
				else
					y = HUD_Y_DEFAULT;
			}
			else
			{
				if (mario_y < ON_CLOUD)
					y = cy_tmp + 233.0f;
				else
					y = HUD_Y_DEFAULT;
			}

		}
	}
	else
	{
		y = HUD_Y_DEFAULT;
		mario->setIsFallDown(false);
	}
	if (cy < -300.0f)
		y = HUD_Y_HIDDEN;


	//in worldmap
	if (mario->getIsInMap())
	{
		x = HUD_WIDTH / 2;
		y = HUD_Y_DEFAULT;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUD_WIDTH / 2;
	t = y - HUD_HEIGHT / 2;
	r = l + HUD_WIDTH;
	b = t + HUD_HEIGHT;
}

//CHUD* CHUD::GetInstance()
//{
//	if (__instance == NULL) __instance = new CHUD(initialX, initialY);
//	return __instance;
//}