#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTIONBLOCK 15000

#define	QUESTIONBLOCK_WIDTH 24
#define QUESTIONBLOCK_BBOX_WIDTH 24
#define QUESTIONBLOCK_BBOX_HEIGHT 24

class CQuestionBlock : public CGameObject {
public:
	CQuestionBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
};


