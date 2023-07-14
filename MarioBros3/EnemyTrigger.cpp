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
	this->IsAdded = false;
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
		if (enemyObject != nullptr )
		{
			if (enemyObject->getx() > 0)
			{
				float e_x = 0.0f, e_y = 0.0f;
				float p_x = 0.0f, p_y = 0.0f;
				enemyObject->GetPosition(e_x, e_y);
				CPlayScene::player->GetPosition(p_x, p_y);

				//Out current Frame?
				if (abs(e_x - p_x) > ENEMY_TRIGGER_SCOPE_WIDTH / 1.5f)
				{
					enemyObject->SetPosition(-100.0f, 100.0f);
				}
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEnemyTrigger::CreateEnemy()
{
	//not delete object in enemytrigger [not find any way to guarantee that not happen bug like : thrown exception read violation,...]
	if (enemyObject != NULL)
	{
		if (enemyObject->getx() > 0.0f)
			return;
	}
	DebugOut(L"create\n");
	switch (type)
	{
	case ENEMY_KOOPAS:
		if (enemyObject == nullptr)
			enemyObject = new CKoopas(pos_x, pos_y, 1);
		else
		{
			CKoopas* koo = dynamic_cast<CKoopas*>(enemyObject);
			koo->SetPosition(pos_x, pos_y);
			koo->SetState(KOOPAS_STATE_WALKING_LEFT);
			koo->setVx(-KOOPAS_WALKING_SPEED);
			koo->setNx(-1);
		}
		break;
	case ENEMY_GREEN_KOOPAS:
		if(enemyObject == nullptr)
			enemyObject = new CKoopas(pos_x, pos_y, 2);
		else
		{
			CKoopas* koo = dynamic_cast<CKoopas*>(enemyObject);
			koo->SetPosition(pos_x, pos_y);
			koo->SetState(KOOPAS_STATE_WALKING_LEFT);
			koo->setVx(-KOOPAS_WALKING_SPEED);
			koo->setNx(-1);
		}
		break;
	case ENEMY_WING_KOOPAS:
		if (enemyObject == nullptr)
			enemyObject = new CKoopas(pos_x, pos_y, 3);
		else
		{
			CKoopas* koo = dynamic_cast<CKoopas*>(enemyObject);
			koo->SetPosition(pos_x, pos_y);
			koo->SetState(JUMP_KOOPAS_STATE_JUMPING);
			koo->setVx(-KOOPAS_WALKING_SPEED);
			koo->setNx(-1);
		}
		break;
	case ENEMY_GOOMBA:
		if (enemyObject == nullptr)
			enemyObject = new CGoomba(pos_x, pos_y);
		else
		{
			enemyObject->SetPosition(pos_x, pos_y);
			enemyObject->SetState(GOOMBA_STATE_WALKING);
		}
		break;
	case ENEMY_RED_GOOMBA:
		if(enemyObject == nullptr)
			enemyObject = new CRedGoomba(pos_x, pos_y);
		else
		{
			enemyObject->SetPosition(pos_x, pos_y);
			enemyObject->SetState(RED_GOOMBA_STATE_WALKING_WITH_WINGS);
		}
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

	if (!IsAdded)
	{
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
		IsAdded = true;
	}
}