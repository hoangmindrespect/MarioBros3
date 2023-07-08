#pragma once

#include "GameObject.h"
#include "Coin.h"
#include "Animation.h"
#include "Animations.h"
#include "Koopas.h"
#include "RedGoomba.h"

#define ENEMY_TRIGGER_SCOPE_WIDTH	256
#define ENEMY_TRIGGER_SCOPE_HEIGHT	272

#define ENEMY_KOOPAS	1
#define ENEMY_GREEN_KOOPAS	5
#define ENEMY_WING_KOOPAS	2
#define ENEMY_GOOMBA	3
#define	ENEMY_RED_GOOMBA	4
#define	ENEMY_RED_GOOMBA_ONE_TIME	6
#define	ENEMY_GOOMBA_ONE_TIME	7

//1: create koopas
//2: create wing koopas
//3: create goomba
//4: create red goomba

class CEnemyTrigger : public CGameObject {
	int type;
	LPGAMEOBJECT enemyObject;
	bool IsCreated;
	float pos_x;
	float pos_y;
public:
	CEnemyTrigger(float x, float y, int z, float pos_x,float pos_y);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	int getType() { return type; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	LPGAMEOBJECT getEnemyObject() { return enemyObject; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void CreateEnemy();
};



