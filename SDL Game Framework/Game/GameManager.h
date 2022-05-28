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
	// �÷��̾� ������ (���� ������)
	PlayerData	pData;

	// �÷��̾� ĳ����
	Player		player;

	// ��
	Map			map;
	Trap		Trap;

}GameManager;

void GameManager_Init(GameManager* gdata);

void GameManager_Update(GameManager* gdata);

void GameManager_Render(GameManager* gdata);

void GameManager_Release(GameManager* gdata);

void SaveData(GameManager* gdata);