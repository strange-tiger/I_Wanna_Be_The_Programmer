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

	// 플레이어 데이터 저장 << 나중에 함수로 빼서 Save() 필요할 때 사용
	gdata->pData.mapSaveID = 3;
	gdata->pData.playerSavePos.X = 10;
	gdata->pData.playerSavePos.Y = 20;
	gdata->pData.youDieCount = 99;

	fwrite(&gdata->pData, sizeof(gdata->pData), 1, savefp);
	fclose(savefp);
}