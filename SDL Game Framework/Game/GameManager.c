#include "stdafx.h"
#include "Game/GameManager.h"

FILE* savefp;

void GameManager_Init(GameManager* gdata)
{
	if (savefp = fopen("saveData.bin", "rb"))
	{
		LogInfo("saveData : true");
		// ���̺� ���� �ε�
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

		// ���̺� ���� ����
		SaveData(gdata);
	}
	
	// csv������ ����
	CsvFile csvFile = { 0 }; // TODO : Csv.h�� MAXIMUM_ROW ����
	CreateCsvFile(&csvFile, "CsvTest.csv"); // TODO : csv �����̸� ����

	// Game ����
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