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
	this->IsCreated = false;
}

void CEnemyTrigger::Render()
{
	RenderBoundingBox();
}

void CEnemyTrigger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ENEMY_TRIGGER_SCOPE_WIDTH / 2;
	t = y - ENEMY_TRIGGER_SCOPE_HEIGHT / 2;
	r = l + ENEMY_TRIGGER_SCOPE_WIDTH;
	b = t + ENEMY_TRIGGER_SCOPE_HEIGHT;
}

void CEnemyTrigger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	if (type == 6 || type == 7){}
	else
	{
		if (enemyObject != NULL)
		{
			float e_x = 0.0f, e_y = 0.0f;
			float p_x = 0.0f, p_y = 0.0f;
			enemyObject->GetPosition(e_x, e_y);
			CPlayScene::player->GetPosition(p_x, p_y);
			if (abs(e_x - p_x) > ENEMY_TRIGGER_SCOPE_WIDTH / 1.5f)
			{
				if (!enemyObject->IsDeleted())
				{
					enemyObject->Delete();
					enemyObject = NULL;
				}
				else
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
	case ENEMY_RED_GOOMBA_ONE_TIME:
		if (!IsCreated)
		{
			enemyObject = new CRedGoomba(pos_x, pos_y);
			IsCreated = true;
			break;
		}
		else
			break;
	case ENEMY_GOOMBA_ONE_TIME:
		if (!IsCreated)
		{
			enemyObject = new CGoomba(pos_x, pos_y);
			IsCreated = true;
			break;
		}
		else
			break;
	default:
		break;
	}

	if (type == ENEMY_KOOPAS)
	{
		CKoopas* k = dynamic_cast<CKoopas*>(enemyObject);
		if (k->getType() == 1)
		{
			CKoopasNavigation* a = new CKoopasNavigation(enemyObject->getx() - KOOPAS_NAVIGATION_WIDTH - 2.0f, enemyObject->gety() + 6.0f);
			a->setHost(dynamic_cast<CKoopas*>(enemyObject));
			CPlayScene::objects.push_back(a);
		}
	}

	for (int i = 0; i < CPlayScene::objects.size(); i++)
	{
		if (dynamic_cast<CMario*>(CPlayScene::objects[i]))
		{
			CPlayScene::objects.insert(CPlayScene::objects.begin() + i - 1, enemyObject);
			break;
		}
	}
}