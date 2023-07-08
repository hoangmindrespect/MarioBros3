#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"


class CPlayScene: public CScene
{
protected:
public:
	// A play scene has to have player, right? 
	static LPGAMEOBJECT player;
	static vector<LPGAMEOBJECT> objects;
	static vector<LPGAMEOBJECT> stop;

	//player data
	static int turn;
	static int point;
	static int coin;

	//pipe BOOLEAN
	static bool isGetInDown;				//di chuyển vào pipe theo hướng từ trên xuống
	static bool isGetInUp;					// di chuyển vào pipe theo chiều từ dưới lên
	static bool isGetOutDown;					// di chuyển ra pipe theo chiều từ tren xuống
	static bool isGetOutUp;					// di chuyển ra pipe theo chiều từ dưới lên
	static float tempoPosition;				// vi trí tạm thời của mario khi đi vào ống nước.
	static float Y_target;
	static float X_target;
	static ULONGLONG time_start;
	static ULONGLONG time_end;
	float default_y = 0.0f;
	void AddObject(LPGAMEOBJECT e);
	void AddObject1(LPGAMEOBJECT e);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	static bool IsIntroScene() { return (!player) ? true : false; }
	void Clear();
	void PurgeDeletedObjects();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	static bool IsOutOfBound(LPGAMEOBJECT a);

};

typedef CPlayScene* LPPLAYSCENE;



