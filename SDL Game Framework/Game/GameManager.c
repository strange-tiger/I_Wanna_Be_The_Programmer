#include "stdafx.h"
#include "Game/GameManager.h"

FILE* savefp;

void GameManager_Init(GameManager* gdata)
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
	
	// csv데이터 세팅
	CsvFile csvFile = { 0 }; // TODO : Csv.h의 MAXIMUM_ROW 수정
	CreateCsvFile(&csvFile, "CsvTest.csv"); // TODO : csv 파일이름 수정

	// Game 세팅
	Player_Init(&gdata->player);
	Map_Init(&gdata->map);
}

void GameManager_Update(GameManager* gdata)
{
	Player_Update(&gdata->player, &gdata->map);
	Map_Update(&gdata->map);
}

void GameManager_Render(GameManager* gdata)
{
	Player_Render(&gdata->player);
	Map_Render(&gdata->map);
}

void GameManager_Release(GameManager* gdata)
{
	Player_Release(&gdata->player);
	Map_Release(&gdata->map);
}

void SaveData(GameManager* gdata)
{
	savefp = fopen("saveData.bin", "wb");

	gdata->pData.mapSaveID = gdata->map.ID;
	gdata->pData.playerSavePos.X = gdata->map.RespawnPoint.X;
	gdata->pData.playerSavePos.Y = gdata->map.RespawnPoint.Y;

	fwrite(&gdata->pData, sizeof(gdata->pData), 1, savefp);
	fclose(savefp);
}