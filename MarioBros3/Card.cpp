#include "Card.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "PlayScene.h"
#include "Game.h"

void CCard::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == CARD_STATE_EMPTY)
		animations->Get(ID_CARD_EMPTY)->Render(x, y);
	else if (state == CARD_STATE_FLICKING_MUSH)
		animations->Get(ID_CARD_MUSHROOM_FLICKING)->Render(x, y);
	else if (state == CARD_STATE_FLICKING_FLOW)
		animations->Get(ID_CARD_FLOWER_FLICKING)->Render(x, y);
	else if (state == CARD_STATE_FLICKING_STAR)
		animations->Get(ID_CARD_STAR_FLICKING)->Render(x, y);
	else if (state == CARD_STATE_MUSH_STATIC)
		animations->Get(ID_CARD_MUSHROOM)->Render(x, y);
	else if (state == CARD_STATE_FLOW_STATIC)
		animations->Get(ID_CARD_FLOWER)->Render(x, y);
	else if (state == CARD_STATE_STAR_STATIC)
		animations->Get(ID_CARD_STAR)->Render(x, y);
	//RenderBoundingBox();
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGame* game = CGame::GetInstance();
	float cx, cy;
	float mario_x, mario_y;

	mario->GetPosition(cx, cy);
	mario->GetPosition(mario_x, mario_y);
	float cy_tmp = cy - game->GetBackBufferHeight() / 2;
	cx -= game->GetBackBufferWidth() / 2;

	//update state
	if (position == 0)
		state = CPlayScene::card_first->GetState();
	else if (position == 1)
		state = CPlayScene::card_second->GetState();
	else if(position == 2)
		state = CPlayScene::card_third->GetState();

	if (CPlayScene::destination_point != -1.0f && mario_x > CPlayScene::destination_point)
		return;

	//in normal scene
	if (cx < 0)
		x = CARD_X_DEFAULT + position * 25.0f;
	else
		x = cx + CARD_X_DEFAULT + position * 25.0f;

	if (mario_y < COORDINATES_ADJUST_CAMERA_FIRST)
	{
		if (mario->GetState() == MARIO_STATE_FLYING)
		{
			if (mario_y < COORDINATES_ADJUST_CAMERA_SECOND)
				y = -107.0f;
			else
				y = cy_tmp + 247.0f;
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
						y = -107.0f;
					else
						y = cy_tmp + 225.0f;
				}
				else
					y = CARD_Y_DEFAULT;
			}
			else
			{
				if (mario_y < ON_CLOUD)
					y = cy_tmp + 225.0f;
				else
					y = CARD_Y_DEFAULT;
			}
		}
	}
	else
	{
		y = CARD_Y_DEFAULT;
		mario->setIsFallDown(false);
	}

	if (cy < -300.0f)
		y = CARD_Y_HIDDEN;

	//in world map
	if (mario->getIsInMap())
	{
		x = CARD_X_DEFAULT + position * 25.0f;
		y = CARD_Y_DEFAULT;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}

void CCard::setStateFlicking(CGoal* goal)
{
	if (goal->getResult() == 1)
		this->SetState(CARD_STATE_FLICKING_STAR);
	else if (goal->getResult() == 2)
		this->SetState(CARD_STATE_FLICKING_MUSH);
	else
		this->SetState(CARD_STATE_FLICKING_FLOW);
}
void CCard::setStateStatic()
{
	if (this->GetState() == CARD_STATE_FLICKING_STAR)
		this->SetState(CARD_STATE_STAR_STATIC);
	if (this->GetState() == CARD_STATE_FLICKING_MUSH)
		this->SetState(CARD_STATE_MUSH_STATIC);
	if (this->GetState() == CARD_STATE_FLICKING_FLOW)
		this->SetState(CARD_STATE_FLOW_STATIC);
}