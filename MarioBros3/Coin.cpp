#include "Coin.h"
#include "Effect.h"
#include "QuestionBlock.h"
#include "PlayScene.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	RenderBoundingBox();
}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
	if (isInQuestionBlock == 1)
	{
		if (IsUp == false && y > maxy)
			y -= 0.3f * dt;
		else
		{
			IsUp = true;
			if (IsDown == false && y < miny)
				y += 0.2f * dt;
			else
			{
				y = miny;
				IsDown = true;
				this->Delete();
				CEffect* a = new CEffect(x, y, 6);
				CPlayScene::objects.push_back(a);
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}