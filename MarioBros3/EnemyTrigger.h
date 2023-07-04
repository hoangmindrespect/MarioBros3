#pragma once
class EnemyTrigger
{
};
#pragma once

#include "GameObject.h"
#include "Coin.h"
#include "Animation.h"
#include "Animations.h"

//1: create koopas
//2: create wing koopas
//3: create goomba
//4: create red goomba

class CEnemyTrigger : public CGameObject {
	int type;//1: coin, 2: redmush, 3: greenmush, 4: leaf

public:
	CEnemyTrigger(float x, float y, int z) : CGameObject(x, y) {
		type = z;
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	int getType() { return type; }
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};



