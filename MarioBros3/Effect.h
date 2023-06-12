#pragma once
    class Effect
{
};
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11900

#define	COIN_WIDTH 16
#define COIN_BBOX_WIDTH 16
#define COIN_BBOX_HEIGHT 16

	class CEffect : public CGameObject {
		int type;
		float ax;
		float ay;

	public:
		CEffect(float x, float y, int k);
		void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		void GetBoundingBox(float& l, float& t, float& r, float& b);
		virtual void OnNoCollision(DWORD dt);

		int IsBlocking() { return 0; }
	};




