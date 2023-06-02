#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CMarioStop : public CGameObject
{
protected:
	int spriteID;
	int canMoveRight;
	int canMoveLeft;
	int canMoveDown;
	int canMoveUp;
	int idScene;
	int type; // no box or is aboxx
public:
	CMarioStop(float x, float y, int sprite,
	int canMoveRight,
	int canMoveLeft,
	int canMoveDown,
	int canMoveUp,
	int idScene, int k) :CGameObject(x, y)
	{
		this->spriteID = sprite;
		this->canMoveDown = canMoveDown;
		this->canMoveLeft = canMoveLeft;
		this->canMoveRight = canMoveRight;
		this->canMoveUp = canMoveUp;
		this->idScene = idScene;
		this->type = k;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int getCanMoveDown() { return canMoveDown; }
	int getCanMoveUp() { return canMoveUp; }
	int getCanMoveRight() { return canMoveRight; }
	int getCanMoveLeft() { return canMoveLeft; }
	int getType() { return type; }
	int getIDScene() { return idScene; }
};
typedef CMarioStop* LPMARIOSTOP;


