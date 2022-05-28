#pragma once

#include "Type.h"

#include "Game/Player.h"
#include "Game/Map.h"
#include "Game/Trap.h"

typedef struct PlayerData
{
	int32		mapSaveID;	
	Position	playerSavePos;	
	int32		youDieCount;	
}PlayerData;

typedef struct GameManager
{
	// 플레이어 데이터 (저장 데이터)
	PlayerData	pData;

	// 플레이어 캐릭터
	Player		player;

	// 맵
	Map			map;
	Trap		Trap;

}GameManager;

void GameManager_Init(GameManager* gdata);

void GameManager_Update(GameManager* gdata);

void GameManager_Render(GameManager* gdata);

void GameManager_Release(GameManager* gdata);

void SaveData(GameManager* gdata);