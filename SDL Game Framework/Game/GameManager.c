#include "stdafx.h"
#include "Game/GameManager.h"

FILE* savefp;

void init_GameManager(GameManager* gdata)
{
	if (savefp = fopen("saveData.bin", "rb"))
	{
		LogInfo("saveData : true");
		// 세이브 파일 로드
		while (fread(&gdata->pData, sizeof(gdata->pData), 1, savefp) == 1)
		{
		}
		LogInfo("map : %d", gdata->pData.mapSaveID);
		LogInfo("POS.X : %d", gdata->pData.playerSavePos.X);
		LogInfo("POS.Y : %d", gdata->pData.playerSavePos.Y);
		LogInfo("DIECOUNT : %d", gdata->pData.youDieCount);

		fclose(savefp);
	}
	else
	{
		LogInfo("saveData : false");

		// 세이브 파일 생성
		SaveData(gdata);
	}
}

void update_GameManager(GameManager* gdata)
{

}

void render_GameManager(GameManager* gdata)
{

}

void release_GameManager(GameManager* gdata)
{

}

void SaveData(GameManager* gdata)
{
	savefp = fopen("saveData.bin", "wb");

	gdata->pData.mapSaveID = 3; // 맵 아이디 나중에 추가되면
	gdata->pData.playerSavePos.X = 10; // gdata->Player.position.Y
	gdata->pData.playerSavePos.Y = 20; // gdata->Player.position.Y
	gdata->pData.youDieCount = 99; // Player.c -> Player_Die()에서 카운트

	fwrite(&gdata->pData, sizeof(gdata->pData), 1, savefp);
	fclose(savefp);
}