#pragma once

#include "Type.h"

#include "Game/Player.h"
#include "Game/Map.h"
#include "Game/Trap.h"

typedef struct PlayerData
{
	int32		mapSaveID;		// Map�� ID ���� �߰��Ǵ� ���� �ֳ�?
	Position	playerSavePos;	// data->Trap.RespawnPoint
	int32		youDieCount;	// Player_isDead���� Count ����
}PlayerData;

typedef struct GameManager
{
	// �÷��̾� ������
	PlayerData	pData;

	// �÷��̾� ĳ����
	Player		player;

	// �� ������
	Map			map;
	Trap		Trap;

}GameManager;

void init_GameManager(GameManager* gdata);

void update_GameManager(GameManager* gdata);

void render_GameManager(GameManager* gdata);

void release_GameManager(GameManager* gdata);

void SaveData(void);