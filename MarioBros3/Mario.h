#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "PlayScene.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.08f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0003f
#define MARIO_ACCEL_RUN_X	0.0005f

#define MARIO_JUMP_SPEED_Y		0.28f
#define MARIO_JUMP_RUN_SPEED_Y	0.4f

#define MARIO_GRAVITY			0.0005f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_LOW_FLY			309
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_PREPARE_RUNNING_RIGHT	11258
#define MARIO_STATE_PREPARE_RUNNING_LEFT	11259

#define MARIO_STATE_RELEASE_RUNNING_RIGHT	1258
#define MARIO_STATE_RELEASE_RUNNING_LEFT	1259

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define TIME_READY_TO_RUN	3000

#define MARIO_STATE_ATTACK_RIGHT	178
#define MARIO_STATE_ATTACK_LEFT	179

#define MARIO_STATE_FLYING_RIGHT	168
#define MARIO_STATE_FLYING_LEFT	169

#define MARIO_STATE_RELEASE_FLYING_RIGHT	128
#define MARIO_STATE_RELEASE_FLYING_LEFT	129

#define MARIO_STATE_IN_MAP	9991


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// TAIL MARIO
#define ID_ANI_MARIO_TAIL_IDLE_RIGHT 1700
#define ID_ANI_MARIO_TAIL_IDLE_LEFT 1701

#define ID_ANI_MARIO_TAIL_WALKING_RIGHT 1703
#define ID_ANI_MARIO_TAIL_WALKING_LEFT 1702
#define ID_ANI_MARIO_TAIL_READY_TO_RUN_RIGHT 1703
#define ID_ANI_MARIO_TAIL_READY_TO_RUN_LEFT 1702

#define ID_ANI_MARIO_TAIL_RUNNING_RIGHT 1705
#define ID_ANI_MARIO_TAIL_RUNNING_LEFT 1704

#define ID_ANI_MARIO_TAIL_BRACE_RIGHT 1707
#define ID_ANI_MARIO_TAIL_BRACE_LEFT 1706

#define ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT 1708
#define ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT 1709


#define ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT 1710
#define ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT 1711

#define ID_ANI_MARIO_TAIL_SIT_RIGHT 1712
#define ID_ANI_MARIO_TAIL_SIT_LEFT 1713

#define ID_ANI_MARIO_TAIL_ATTACK_RIGHT	1714
#define ID_ANI_MARIO_TAIL_ATTACK_LEFT	1715

#define ID_ANI_MARIO_TAIL_FLYING_RIGHT	1716
#define ID_ANI_MARIO_TAIL_FLYING_LEFT	1717

#define ID_ANI_MARIO_TAIL_LOW_FLYING_RIGHT	1718
#define ID_ANI_MARIO_TAIL_LOW_FLYING_LEFT	1719

#define ID_ANI_MARIO_SMALL_IN_MAP	1720

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL		3
#define MARIO_BIG_BBOX_WIDTH  16
#define MARIO_BIG_BBOX_HEIGHT 26

#define MARIO_TAIL_BBOX_WIDTH  24
#define MARIO_TAIL_BBOX_HEIGHT 26

#define MARIO_BIG_SITTING_BBOX_WIDTH  16
#define MARIO_BIG_SITTING_BBOX_HEIGHT 18

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_ATTACK_TIME 500
#define MARIO_TIME_TO_RUN 1500
#define MARIO_FLYING_TIME 5000
#define MARIO_BRACE_TIME 1000
class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isReadyToRun;
	BOOLEAN	isAttackByTail;
	BOOLEAN isOnPlatform;
	BOOLEAN isRun;
	BOOLEAN isFlying;
	BOOLEAN isReleaseFlying; // mario landing or flying?
	BOOLEAN isChangeDirection;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG attack_start;
	ULONGLONG running_start;
	ULONGLONG flying_start;
	ULONGLONG bracing_start;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithRedMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithRedBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithRedPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);

	void SetYWhenCollideColorbox(LPGAMEOBJECT gameobject);
	

	int GetAniIdBig();
	int GetAniIdTail();
	int GetAniIdSmall();

	int IsInMap;
public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		//IsInMap = k;
		isChangeDirection = false;
		isSitting = false;
		isAttackByTail = false;
		isReadyToRun = false;
		isFlying = false;
		isRun = false;
		isReleaseFlying = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		attack_start = -1;
		running_start = 0;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void setLevel(int i) { level = i; }
	void setIsInMap(int k) { IsInMap = k; }
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetIsRun(bool a) { isRun = a; }
	void SetIsReadyToRun(bool a) { isReadyToRun = a; }
	void SetIsFlying(bool a) { isFlying = a; }
	void SetIsReleaseFlying(bool a) { isReleaseFlying = a; }
	bool getIsReleaseFlying() {return isReleaseFlying; }

	void SetVy(float v) { vy = v; }
	void SetVx(float v) { vx = v; }
	int getlevel() { return level; }
	int getnx() { return nx; }
	float getvx() { return vx; }
	bool getIsRun() { return isRun; }
	bool getIsFlying() { return isFlying; }
};

