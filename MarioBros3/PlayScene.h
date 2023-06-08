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

public:
	// A play scene has to have player, right? 
	static LPGAMEOBJECT player;					
	static vector<LPGAMEOBJECT> objects;
	static vector<LPGAMEOBJECT> stop;
	float i = 44.0f;
	vector<int> index;
	BOOLEAN isCreateGoomba = false;
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

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;



