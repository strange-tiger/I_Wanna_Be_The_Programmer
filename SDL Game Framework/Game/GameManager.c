#include "stdafx.h"
#include "Game/GameManager.h"

FILE* savefp;

void init_GameManager(GameManager* gdata)
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

	gdata->pData.mapSaveID = 3; // �� ���̵� ���߿� �߰��Ǹ�
	gdata->pData.playerSavePos.X = 10; // gdata->Player.position.Y
	gdata->pData.playerSavePos.Y = 20; // gdata->Player.position.Y
	gdata->pData.youDieCount = 99; // Player.c -> Player_Die()���� ī��Ʈ

	fwrite(&gdata->pData, sizeof(gdata->pData), 1, savefp);
	fclose(savefp);
}