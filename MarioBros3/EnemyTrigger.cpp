#include "EnemyTrigger.h"
#include "debug.h"
#include "PlayScene.h"
#include "KoopasNavigation.h"

CEnemyTrigger::CEnemyTrigger(float x, float y, int type, float pos_x, float pos_y)
{
	this->enemyObject = NULL;
	this->x = x;
	this->y = y;
	this->type = type;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

void CEnemyTrigger::Render()
{
	RenderBoundingBox();
}

void CEnemyTrigger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ENEMY_TRIGGER_SCOPE / 2;
	t = y - ENEMY_TRIGGER_SCOPE / 2;
	r = l + ENEMY_TRIGGER_SCOPE;
	b = t + ENEMY_TRIGGER_SCOPE;
}

void CEnemyTrigger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	if (enemyObject != NULL)
	{
		float e_x = 0.0f, e_y = 0.0f;
		float p_x = 0.0f, p_y = 0.0f;
		enemyObject->GetPosition(e_x, e_y);
		CPlayScene::player->GetPosition(p_x, p_y);
		if (abs(e_x - p_x) > ENEMY_TRIGGER_SCOPE / 1.5f)
		{
			if (enemyObject != NULL)
			{
				enemyObject->Delete();
				enemyObject = NULL;
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEnemyTrigger::CreateEnemy()
{
	if (enemyObject != NULL)
		return;
	switch (type)
	{
	case ENEMY_KOOPAS:
		enemyObject = new CKoopas(pos_x, pos_y, 1);
		break;
	case ENEMY_GREEN_KOOPAS:
		enemyObject = new CKoopas(pos_x, pos_y, 2);
		break;
	case ENEMY_WING_KOOPAS:
		enemyObject = new CKoopas(pos_x, pos_y, 3);
		break;
	case ENEMY_GOOMBA:
		enemyObject = new CGoomba(pos_x, pos_y);
		break;
	case ENEMY_RED_GOOMBA:
		enemyObject = new CRedGoomba(pos_x, pos_y);
		break;
	default:
		break;
	}

	if (type == ENEMY_KOOPAS)
	{
		CKoopasNavigation* a = new CKoopasNavigation(1.0f, enemyObject->gety());
		a->setHost(dynamic_cast<CKoopas*>(enemyObject));
		CPlayScene::objects.push_back(a);
	}
	CPlayScene::objects.insert(CPlayScene::objects.end() - 20, enemyObject);
}