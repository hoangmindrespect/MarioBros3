#pragma once
#include "GameObject.h"
#include "Koopas.h"
#include "Animation.h"
#include "Animations.h"
#include "PlayScene.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.08f
#define MARIO_PREPARE_RUNNING_SPEED		0.12f

#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0004f
#define MARIO_ACCEL_RUN_X	0.0006f

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
#define MARIO_STATE_HOLDING_KOOPAS 1260
#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define TIME_READY_TO_RUN	3000

#define MARIO_STATE_ATTACK_RIGHT	178
#define MARIO_STATE_ATTACK_LEFT	179

#define MARIO_STATE_FLYING	168

#define MARIO_STATE_RELEASE_FLYING	128

#define MARIO_STATE_IN_MAP	9991


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_PREPARE_RIGHT 520
#define ID_ANI_MARIO_PREPARE_LEFT 521

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

#define ID_ANI_MARIO_HOLD_WALK_RIGHT 1006
#define ID_ANI_MARIO_HOLD_WALK_LEFT 1007

#define ID_ANI_MARIO_HOLD_JUMP_RIGHT 1008
#define ID_ANI_MARIO_HOLD_JUMP_LEFT 1009

#define ID_ANI_MARIO_HOLD_IDLE_RIGHT 1004
#define ID_ANI_MARIO_HOLD_IDLE_LEFT 1005

#define ID_ANI_MARIO_KICK_RIGHT 1002
#define ID_ANI_MARIO_KICK_LEFT 1003

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

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1602
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1603

#define ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT 1606
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT 1607

#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 1608
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 1609

#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 1604
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 1605

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

#define ID_ANI_MARIO_TAIL_KICK_RIGHT 1721
#define ID_ANI_MARIO_TAIL_KICK_LEFT 1722

#define ID_ANI_MARIO_TAIL_HOLD_WALK_RIGHT 1723
#define ID_ANI_MARIO_TAIL_HOLD_WALK_LEFT 1724

#define ID_ANI_MARIO_TAIL_HOLD_JUMP_RIGHT 1725
#define ID_ANI_MARIO_TAIL_HOLD_JUMP_LEFT 1726

#define ID_ANI_MARIO_TAIL_HOLD_IDLE_RIGHT 1727
#define ID_ANI_MARIO_TAIL_HOLD_IDLE_LEFT 1728

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

#define MARIO_SMALL_BBOX_WIDTH  10
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_ATTACK_TIME 500
#define MARIO_TIME_TO_RUN 1500
#define MARIO_FLYING_TIME 5000
#define MARIO_BRACE_TIME 1000


class CMario : public CGameObject
{
	BOOLEAN isEndTurn; // user for moving in map
	BOOLEAN isMoveLeft;
	BOOLEAN isMoveRight;
	BOOLEAN isMoveUp;
	BOOLEAN isMoveDown;

	BOOLEAN isSwitch;
	BOOLEAN isRealse;
	BOOLEAN isFlying;
	BOOLEAN isSitting;
	BOOLEAN	isAttackByTail;
	BOOLEAN isOnPlatform;
	BOOLEAN isOnCloud; // use to check if mario on high cloud and if mario fall down, this variable is condition to set cam

	BOOLEAN isHolding;
	BOOLEAN isKicking;
	// handle flying
	BOOLEAN isChangeDirection;
	BOOLEAN isStart; // biến bool để tính thời gian bay

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float xtmp, ytmp;
	int level; 
	int untouchable;
	ULONGLONG die_start;
	ULONGLONG untouchable_start;
	ULONGLONG attack_start;
	ULONGLONG running_start;
	ULONGLONG flying_start;
	ULONGLONG bracing_start;
	ULONGLONG kicking_start;

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

	

	int GetAniIdBig();
	int GetAniIdTail();
	int GetAniIdSmall();

	int IsInMap;
	CKoopas* Koopas = NULL;
public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		//IsInMap = k;
		isEndTurn = isMoveDown = isMoveLeft = isMoveRight = isMoveUp = isSwitch = false;;
		isChangeDirection = false;
		isSitting = false;
		isAttackByTail = false;
		isFlying = false;
		isRealse = false;
		isOnCloud = false;
		isHolding = false;
		isKicking = false;

		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		attack_start = -1;
		running_start = 0;
		isOnPlatform = false;
		isSwitch = false;
		coin = 0;
		
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void setLevel(int i) { level = i; }
	void setIsInMap(int k) { IsInMap = k; }
	void Setax(float k) { ax = k; }
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	//set

	void SetLevel(int l);
	void SetVy(float v) { vy = v; }
	void SetVx(float v) { vx = v; }
	void SetIsMoveUp(bool a) { isMoveUp = a; }
	void SetIsMoveDown(bool a) { isMoveDown = a; }
	void SetIsMoveRight(bool a) { isMoveRight = a; }
	void SetIsMoveLeft(bool a) { isMoveLeft = a; }
	void SetIsRelease(bool a) { isRealse = a; }
	void SetIsSwitch(bool a) {isSwitch = a;}
	void SetIsFlying(bool a) { isFlying = a; }
	void setMaxVx(float a) { maxVx = a; }
	void setNx(int a) { nx = a; }
	void setIsOnPlatForm(bool a) { isOnPlatform = a; }
	void setIsOnClound(bool a) { isOnCloud = a; }

	//get 

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int getlevel() { return level; }
	int getnx() { return nx; }
	float getvx() { return vx; }

	int getIsInMap() { return IsInMap; }
	bool getIsMoveUp() { return isMoveUp ; }
	bool getIsMoveDown() { return isMoveDown; }
	bool getIsMoveRight() { return isMoveRight; }
	bool getIsMoveLeft() { return isMoveLeft; }
	bool getIsOnPlatForm() { return isOnPlatform; }
	bool getIsOnCloud() { return isOnCloud; }
	ULONGLONG getFlyingStart() { return flying_start; }
};

