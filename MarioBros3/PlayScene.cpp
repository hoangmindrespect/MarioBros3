#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Background.h"
#include "SampleKeyEventHandler.h"
#include "Pipe.h"
#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Bullet.h"
#include "PiranhaPlant.h"
#include "Koopas.h"
#include "HUD.h"
#include "GrassInMap.h"
#include "MarioStop.h"
#include "ColorBox.h"
#include "Curtains.h"
#include "Goal.h"
#include "RedGoomba.h"
#include "Timer.h"
#include "PointInHUD.h"
#include "PowerFlyingHUD.h"
#include "TurnInHUD.h"
#include "CoinInHUD.h"
#include "Funnel.h"

#define DEAD_ZONE 500.0f

using namespace std;

//
std::vector<CGameObject*> CPlayScene::objects;
std::vector<CGameObject*> CPlayScene::stop;
LPGAMEOBJECT CPlayScene::player;

//initial player data
int::CPlayScene::turn = 4;
int::CPlayScene::point = 0;
int::CPlayScene::coin = 0;

//initial logic pipe
bool::CPlayScene::isGetInDown = false;
bool::CPlayScene::isGetInUp = false;
bool::CPlayScene::isGetOutDown = false;
bool::CPlayScene::isGetOutUp = false;
float::CPlayScene::tempoPosition = 0.0f;
float::CPlayScene::X_target = 0.0f;
float::CPlayScene::Y_target = 0.0f;
ULONGLONG CPlayScene::time_start;
ULONGLONG CPlayScene::time_end;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::AddObject1(LPGAMEOBJECT object)
{
	objects.insert(objects.begin() + 180,object);
}

void CPlayScene::AddObject(LPGAMEOBJECT object)
{
	objects.push_back( object);
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		int type = (int)atof(tokens[3].c_str());
		obj = new CMario(x, y);
		player = (CMario*)obj;
		CMario* mario = dynamic_cast<CMario*>(player);
		if (type == 1)
		{
			mario->setIsInMap(1);
		}
		else
			mario->setIsInMap(0);

		

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_RED_GOOMBA: obj = new CRedGoomba(x, y); break;
	case OBJECT_TYPE_KOOPAS: {int model = (int)atof(tokens[3].c_str());
		obj = new CKoopas(x, y, model); break;
	}
	case OBJECT_TYPE_BRICK: 
	{
		int model = (int)atof(tokens[3].c_str());
		obj = new CBrick(x, y, model);
		break;
	}
	case OBJECT_TYPE_COIN: 
	{	
		int model = (int)atof(tokens[3].c_str());
		obj = new CCoin(x, y, model);
		break;
	}
	case OBJECT_TYPE_PIRANHA: 
	{
		int model = (int)atof(tokens[3].c_str());
		obj = new CPiranhaPlant(x, y, model);
		break;
	}
	case OBJECT_TYPE_QUESTIONBLOCK:
	{
		int type = (int)atof(tokens[3].c_str());
		obj = new CQuestionBlock(x, y, type);
		break;
	}
	case OBJECT_TYPE_BACKGROUND:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_id = atoi(tokens[6].c_str());
		obj = new CBackground(
			x, y,
			cell_width, cell_height, length,
			sprite_id
		);

		break;
	}
	case OBJECT_TYPE_GRASS_IN_MAP: obj = new CGrassInMap(x, y); break;
	case OBJECT_TYPE_GOAL: obj = new CGoal(x, y); break;
	case OBJECT_TYPE_PIPE:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());

		obj = new CPipe(
			x, y,
			cell_width, cell_height, height,
			sprite_begin, sprite_middle
		);

		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int block = atoi(tokens[9].c_str());
		int blockKoopas = atoi(tokens[10].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end, block, blockKoopas
		);

		break;
	}
	case OBJECT_TYPE_COLORBOX:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		obj = new CColorBox(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_MARIO_STOP:
	{
		int spriteid = (int)atof(tokens[3].c_str());
		int canMoveRight = (int)atof(tokens[4].c_str());
		int canMoveLeft = (int)atoi(tokens[5].c_str());
		int canMoveDown = (int)atoi(tokens[6].c_str());
		int canMoveUp = (int)atoi(tokens[7].c_str());
		int idScene = (int)atoi(tokens[8].c_str());
		int type = (int)atoi(tokens[9].c_str());

		obj = new CMarioStop(
			x, y,
			spriteid, canMoveRight, canMoveLeft,
			canMoveDown, canMoveUp, idScene, type
		);
		stop.push_back(obj);
		obj = NULL;
		break;
	}
	case OBJECT_TYPE_SCORE: obj = new CHUD(x, y); break;
	case 20: obj = new CCurtains(x, y); break;
	case OBJECT_TYPE_TIMER: obj = new CTimer(x, y); break;
	case OBJECT_TYPE_POINT: obj = new CPointInHUD(x, y); break;
	case OBJECT_TYPE_POWER_FLYING_HUD: obj = new CPowerFlyingHUD(x, y); break;
	case OBJECT_TYPE_TURN_IN_HUD: obj = new CTurnInHUD(x, y); break;
	case OBJECT_TYPE_COIN_IN_HUD: obj = new CCoinInHUD(x, y); break;
	case OBJECT_TYPE_FUNNEL: {
		float xt = (float)atof(tokens[3].c_str());
		float yt = (float)atof(tokens[4].c_str());

		obj = new CFunnel(x, y, xt, yt); break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	if (obj != NULL)
		obj->SetPosition(x, y);


	if(obj != NULL)
		objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way
	CMario* mario = dynamic_cast<CMario*>(player);
	vector<LPGAMEOBJECT> coObjects;

	//Check for not update when Mario level up
	if (mario->getIsChanging())
	{
		if (mario->getlevel() == MARIO_LEVEL_BIG)
		{
			if (GetTickCount64() - mario->getTimeSwitch() > 1000)
				mario->setIsChanging(false);
			else // return not update
				return;
		}
		else if (mario->getlevel() == MARIO_LEVEL_TAIL)
		{
			if (GetTickCount64() - mario->getTimeSwitch() > 500)
				mario->setIsChanging(false);
			else // return not update
				return;
		}
	}

	//Check for not update when Mario delevel
	if (mario->getIsDelevel())
	{
		if (GetTickCount64() - mario->getTimeSwitch() > 500)
			mario->setIsDelevel(false);
		else // return not update
			return;
	}

	//Handle logic when mario getin or getout the pipe [collide with Funnel]

	if (isGetInDown)
	{
		if (GetTickCount64() - time_start > 1000)
		{
			isGetInDown = false;
			time_end = GetTickCount64();
			isGetOutDown = true; // not neccessarry
			mario->setIsGetInOutPipe(false);
		}
		else // return not update
		{
			if(player->gety() < tempoPosition)
				player->sety(mario->gety() + dt * 0.03f);
			else
				mario->SetPosition(X_target, Y_target);
			return;
		}
	}
	if (isGetInUp)
	{
		if (GetTickCount64() - time_start > 600)
		{
			isGetInUp = false;
			time_end = GetTickCount64();
			isGetOutUp = true;
		}
		else // return not update
		{
			if (player->gety() > tempoPosition)
				player->sety(mario->gety() - dt * 0.03f);
			else
			{
				mario->SetPosition(X_target, Y_target);			
				goto THERE;
			}
			return;
		}
	}
	if (isGetOutUp)
	{
		if (mario->getlevel() == MARIO_LEVEL_SMALL)
		{
			if (GetTickCount64() - time_end > 600)
			{
				isGetOutUp = false;
				mario->setIsGetInOutPipe(false);
			}
			else // return not update
			{
				if (player->gety() > Y_target - MARIO_SMALL_BBOX_HEIGHT - 4.0f)
					player->sety(mario->gety() - dt * 0.03f);
				return;
			}
		}
		else
		{
			if (GetTickCount64() - time_end > 850)
			{
				isGetOutUp = false;
				mario->setIsGetInOutPipe(false);
			}
			else // return not update
			{
				if (player->gety() > Y_target - MARIO_BIG_BBOX_HEIGHT + 2.0f)
					player->sety(mario->gety() - dt * 0.03f);
				return;
			}
		}
	}

THERE:
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	mario->Update(dt, &coObjects);
	// Không update những object nằm dưới màn hình => xóa luôn ngoại trừ mario thì set die
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->gety() > DEAD_ZONE)
		{
			if (!dynamic_cast<CMario*>(objects[i]))
			{
				objects[i]->Delete();
			} 
		}
		if(!dynamic_cast<CMario*>(objects[i]))
			objects[i]->Update(dt, &coObjects);
	}

	if (mario->gety() >	DEAD_ZONE)
		mario->SetState(MARIO_STATE_DIE);

	
	if (player == NULL) return;
	/*if (player->getx() > 689)
	{
		if (isCreateGoomba == false)
		{
			CGoomba* g1 = new CGoomba(889, 102);
			CGoomba* g2 = new CGoomba(959, 102);
			CRedGoomba* g3 = new CRedGoomba(1029, 102);
			objects.push_back(g1);
			objects.push_back(g2);
			objects.push_back(g3);
			isCreateGoomba = true;
		}
	}*/

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload
	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	float mario_x = cx;
	float mario_y = cy;
	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	float cyt = cy;
	float fy = 0.0f;

	if (cx < 0) cx = 0;
	if (mario->getIsInMap() == 0)
	{
		if (mario->getlevel() == MARIO_LEVEL_SMALL || mario->getlevel() == MARIO_LEVEL_BIG)
			cy = 0.0f;
		else
		{
			if (mario_y < 77.0f)
			{
				if (mario->GetState() == MARIO_STATE_FLYING)
					cy = cyt + 44.0f;
				else
				{
					if (mario->getIsOnPlatForm() == false)
					{
						if (mario->getIsFallDown() == false)
						{
							if (mario_y < -60.0f)
							{
								mario->setIsFallDown(true);
								//fy = cy + 44.0f;
							}
						}
						else
						{
							if (mario_y > 50.0f)
								mario->setIsFallDown(false);
						}

						if (mario->getIsFallDown() == true)
						{
							cy = cyt;
						}
						else
						{
							cy = 0.0f;
						}
					}
					else
					{
						// xử lý lúc di chuyển trên platform trên cao
						if (mario_y < -60.0f)
						{
							cy = cyt;
						}
						else
						{
							cy = 0.0f;
						}
					}

				}
			}
			else
			{
				cy = 0.0f;
				mario->setIsFallDown(false);
			}
			
		}

		if (mario->gety() > 170.0f)
			cy = 187.5f;
		//mario đến đích
		if (mario->getx() > 2715.71f)
		{
			return;
		}
		CGame::GetInstance()->SetCamPos(cx, cy);
	}
	else
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f /*cy*/);



	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size() - 1; i++)
		objects[i]->Render();
	for (int i = 0; i < stop.size(); i++)
		stop[i]->Render();
	
	objects[objects.size() - 1]->Render();
}


void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
	for (it = stop.begin(); it != stop.end(); it++)
	{
		delete(*it);
	}
	stop.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	for (int i = 0; i < stop.size(); i++)
		delete stop[i];

	objects.clear(); stop.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	for (it = stop.begin(); it != stop.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());

	stop.erase(
		std::remove_if(stop.begin(), stop.end(), CPlayScene::IsGameObjectDeleted),
		stop.end());
}
