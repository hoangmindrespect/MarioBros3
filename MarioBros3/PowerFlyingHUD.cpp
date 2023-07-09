#include "PowerFlyingHUD.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"

void CPowerFlyingHUD::RenderBoundingBox()
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

	float xx = x - POWERFLYINGHUD_WIDTH / 2 + rect.right / 2;
	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPowerFlyingHUD::Render()
{
	CMario* mario = dynamic_cast<CMario*>(CPlayScene::player);
	CSprites* s = CSprites::GetInstance();
	int ratio = (int)mario->getCountTimePrepareRun() / 300; // kiểm tra số mũi tên trắng và đen
	float distance = 0.0f;
	for (int i = 1; i <= ratio; i++)
	{
		s->Get(ID_WHITE_ARROW)->Draw(x + distance, y);
		distance += 8.0f;
	}
	for(int i = ratio + 1; i <= 6; i++)
	{
		s->Get(ID_BLACK_ARROW)->Draw(x + distance, y);
		distance += 8.0f;
	}

	if (ratio == 6)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_BUTTON_FLYING_MODE_WHITE)->Render(x + distance + 3.0f, y);
	}
	else
		s->Get(ID_BUTTON_FLYING_MODE_BLACK)->Draw(x + distance + 3.0f, y);
	RenderBoundingBox();
}

void CPowerFlyingHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGame* game = CGame::GetInstance();
	float cx, cy;
	mario->GetPosition(cx, cy);
	cx -= game->GetBackBufferWidth() / 2;
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	float cy_tmp = cy - game->GetBackBufferHeight() / 2;

	if (CPlayScene::destination_point != -1.0f && mario_x > CPlayScene::destination_point)
		return;

	//in scene
	if (cx < 0)
		x = POWERFLYINGHUD_X_DEFAULT;
	else
		x = cx + POWERFLYINGHUD_X_DEFAULT;

	if (mario_y < 77.0f)
	{
		if (mario->GetState() == MARIO_STATE_FLYING)
		{
			if (mario_y < COORDINATES_ADJUST_CAMERA_SECOND)
				y = -110.0f;
			else
				y = cy_tmp + 244.0f;
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
						y = -110.0f;
					else
						y = cy_tmp + 222.0f;
				}
				else
					y = POWERFLYINGHUD_Y_DEFAULT;
			}
			else
			{
				if (mario_y < ON_CLOUD)
					y = cy_tmp + 222.0f;
				else
					y = POWERFLYINGHUD_Y_DEFAULT;
			}
		}
	}
	else
	{
		y = POWERFLYINGHUD_Y_DEFAULT;
		mario->setIsFallDown(false);
	}

	if (cy < -300.0f)
		y = POWERFLYINGHUD_Y_HIDDEN;

	//in worldmap
	if (mario->getIsInMap())
	{
		x = POWERFLYINGHUD_X_DEFAULT;
		y = POWERFLYINGHUD_Y_DEFAULT;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPowerFlyingHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - POWERFLYINGHUD_WIDTH / 2;
	t = y - POWERFLYINGHUD_HEIGHT / 2;
	r = l + POWERFLYINGHUD_WIDTH;
	b = t + POWERFLYINGHUD_HEIGHT;
}

