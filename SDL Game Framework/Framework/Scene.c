#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"
#include "Framework/Csv.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene
typedef struct TitleSceneData
{
	//배경
	Image	BGImage;
	Music	BGM;

	//그냥 넣은 텍스트 삭제하셔도 됩니당
	Text	mainText;
	Text	NextText;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
	// 타이틀에서 csv데이터 가져온다.
	CsvFile csvFile = { 0 }; // TODO : Csv.h의 MAXIMUM_ROW 수정
	CreateCsvFile(&csvFile, "CsvTest.csv"); // TODO : csv 파일이름 수정

	Text_CreateText(&data->mainText, "d2coding.ttf", 40,L"이거슨 타이틀", wcslen(L"이거슨 타이틀"));
	Text_CreateText(&data->NextText, "d2coding.ttf", 40,L"Space 눌러 다음 씬으로", wcslen(L"Space 눌러 다음 씬으로"));
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


//------------------------------------ ▼ 인게임 메인 씬 ▼ ------------------------------------

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
	// 플레이어 데이터
	// 맵 데이터

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

	// 데이터 로드
	
	// 플레이어,맵 데이터 이니셜라이즈
	
	FILE* savefp;
	if (savefp = fopen("saveData.bin", "rb"))
	{
		LogInfo("saveData : true");
		// 세이브 파일 로드
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

		// 세이브 파일 생성
		savefp = fopen("saveData.bin", "wb");

		// 플레이어 데이터 저장 << 나중에 함수로 빼서 Save() 필요할 때 사용
		data->pData.mapSaveID = 3;
		data->pData.playerSavePos.X = 10;
		data->pData.playerSavePos.Y = 20;
		data->pData.youDieCount = 99;

		fwrite(&data->pData, sizeof(data->pData), 1 , savefp);
		fclose(savefp);
	}


	// 플레이어 데이터가 있으면 가져온다.
	// 플레이어 데이터가 없으면 초기값으로 설정한다.

	// 플레이어 데이터에 해당하는 각 데이터들을 불러온다.
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	// 플레이어 조작은 pdata에서 해주나? 아니지 조작으로 맵이 스위칭되는 애도 있는데
	 
	// 플레이어 데이터 업데이트
	// 맵의 시작 위치에 플레이어를 위치시킨다.
	// 

	// [ 맵 데이터 ]
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
//추가 바람


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