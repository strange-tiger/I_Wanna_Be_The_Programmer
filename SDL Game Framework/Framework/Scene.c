#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"
#include "Framework/Csv.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene
typedef struct TitleSceneData
{
	//���
	Image	BGImage;
	Music	BGM;

	//�׳� ���� �ؽ�Ʈ �����ϼŵ� �˴ϴ�
	Text	mainText;
	Text	NextText;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
	// Ÿ��Ʋ���� csv������ �����´�.
	CsvFile csvFile = { 0 }; // TODO : Csv.h�� MAXIMUM_ROW ����
	CreateCsvFile(&csvFile, "CsvTest.csv"); // TODO : csv �����̸� ����

	Text_CreateText(&data->mainText, "d2coding.ttf", 40,L"�̰Ž� Ÿ��Ʋ", wcslen(L"�̰Ž� Ÿ��Ʋ"));
	Text_CreateText(&data->NextText, "d2coding.ttf", 40,L"Space ���� ���� ������", wcslen(L"Space ���� ���� ������"));
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	SDL_Color bgColor = { 0, 0, 0, 255 };
	SDL_Color textColor = { 255, 255, 255, 255 };
	Renderer_DrawTextShaded(&data->mainText, 10, 10, bgColor, textColor);
	Renderer_DrawTextShaded(&data->NextText, 100, 100, bgColor, textColor);
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Text_FreeText(&data->mainText);
	Text_FreeText(&data->NextText);

	SafeFree(data); 
}
#pragma endregion


//------------------------------------ �� �ΰ��� ���� �� �� ------------------------------------

#pragma region MainScene

typedef struct PlayerData
{
	int32		mapSaveID;
	Position	playerSavePos;
	int32		youDieCount;
}PlayerData;

typedef struct MainSceneData
{
	PlayerData pData;
	// �÷��̾� ������
	// �� ������

} MainSceneData;

void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));

	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	// ������ �ε�
	
	// �÷��̾�,�� ������ �̴ϼȶ�����
	
	FILE* savefp;
	if (savefp = fopen("saveData.bin", "rb"))
	{
		LogInfo("saveData : true");
		// ���̺� ���� �ε�
		while (fread(&data->pData, sizeof(data->pData), 1, savefp) == 1)
		{ 
		}
		LogInfo("map : %d", data->pData.mapSaveID);
		LogInfo("POS.X : %d", data->pData.playerSavePos.X);
		LogInfo("POS.Y : %d", data->pData.playerSavePos.Y);
		LogInfo("DIECOUNT : %d", data->pData.youDieCount);


		fclose(savefp);
	}
	else
	{
		LogInfo("saveData : false");

		// ���̺� ���� ����
		savefp = fopen("saveData.bin", "wb");

		// �÷��̾� ������ ���� << ���߿� �Լ��� ���� Save() �ʿ��� �� ���
		data->pData.mapSaveID = 3;
		data->pData.playerSavePos.X = 10;
		data->pData.playerSavePos.Y = 20;
		data->pData.youDieCount = 99;

		fwrite(&data->pData, sizeof(data->pData), 1 , savefp);
		fclose(savefp);
	}


	// �÷��̾� �����Ͱ� ������ �����´�.
	// �÷��̾� �����Ͱ� ������ �ʱⰪ���� �����Ѵ�.

	// �÷��̾� �����Ϳ� �ش��ϴ� �� �����͵��� �ҷ��´�.
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	// �÷��̾� ������ pdata���� ���ֳ�? �ƴ��� �������� ���� ����Ī�Ǵ� �ֵ� �ִµ�
	 
	// �÷��̾� ������ ������Ʈ
	// ���� ���� ��ġ�� �÷��̾ ��ġ��Ų��.
	// 

	// [ �� ������ ]
	// 
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;


}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region CreditScene
//�߰� �ٶ�


#pragma endregion

bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	case SCENE_CREDIT:
		//g_Scene.Init = init_page;
		//g_Scene.Update = update_page;
		//g_Scene.Render = render_page;
		//g_Scene.Release = release_page;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}

bool Scene_IsGameClose(void) {
	return s_isGameClose;
}