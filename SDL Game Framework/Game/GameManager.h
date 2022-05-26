#pragma once

#include "Type.h"

#include "Game/Player.h"
#include "Game/Map.h"
#include "Game/Trap.h"

typedef struct PlayerData
{
	int32		mapSaveID;		// Map에 ID 값이 추가되는 곳이 있나?
	Position	playerSavePos;	// data->Trap.RespawnPoint
	int32		youDieCount;	// Player_isDead에서 Count 증가
}PlayerData;

typedef struct GameManager
{
	// 플레이어 데이터
	PlayerData	pData;

	// 플레이어 캐릭터
	Player		player;

	// 맵 데이터
	Map			map;
	Trap		Trap;

}GameManager;

void init_GameManager(GameManager* gdata);

void update_GameManager(GameManager* gdata);

void render_GameManager(GameManager* gdata);

void release_GameManager(GameManager* gdata);

void SaveData(void);