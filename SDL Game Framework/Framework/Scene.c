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
	Image	Title_BackGroundImage;
	Image	Title_URL;
	Image	Title_SmallTitle;
	int32		Title_SmallTitle_posY;
	Image	Title_BigTitle;
	int32		Title_BigTitle_posY;
	Image	Title_PressStart;
	Image	Title_GameStart;
	Image	Title_Credit;
	Image	Title_Exit;
	Image	Title_Arrow;
	int32		Title_Arrow_posY;

	float	TitleScenePlayTime;

	Music	BGM;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	

	//Image File Load
	Image_LoadImage(&data->Title_BackGroundImage, "TitleImage01_BackGroundImage.png");
	Image_LoadImage(&data->Title_URL, ".png");
	Image_LoadImage(&data->Title_SmallTitle, ".png");
	Image_LoadImage(&data->Title_BigTitle, ".png");
	Image_LoadImage(&data->Title_PressStart, ".png");
	Image_LoadImage(&data->Title_GameStart, ".png");
	Image_LoadImage(&data->Title_Credit, ".png");
	Image_LoadImage(&data->Title_Exit, ".png");
	Image_LoadImage(&data->Title_Arrow, ".png");


	data->Title_SmallTitle_posY = -600;
	data->Title_BigTitle_posY = -400




	//블랙스크린으로 시작
	//로고 페이드 인(1초) - 유지(3초) - 아웃(1초)
	//애쉬 배경 출력 페이드인(1초)
	//메인타이틀 위에서 아래로Y++; (0.5초)
	//메인타이틀 줌 인 - 아웃 반복(스케일 조정)
	//선택지 선택시마다 강조 효과
	
	
	/*
	선택지
	Start
	Credit
	Exit
	*/


	/*
	Control
	VK_UP
	VK_DOWN
	VK_ENTER
	*/


}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->TitleScenePlayTime += Timer_GetDeltaTime();

	if (data->TitleScenePlayTime < 2)
	{
		Image_SetAlphaValue(0, &data->LogoForBlackScreen - 255, 255);
	}
	if (2 <= data->TitleScenePlayTime && data->TitleScenePlayTime < 3)
	{
		Image_SetAlhpaValue(0, &data->LogoForBlackScreen + 10, 255);
	}
	if (5 <= data->TitleScenePlayTime && data->TitleScenePlayTime < 6)
	{
		Image_SetAlhpaValue(0, &data->LogoForBlackScreen - 10, 255);
	}


	//Input Key in Title Scene 
	if (Input_GetKeyDown(VK_UP) && data->ValueForSelectMenu > 1 )
	{
		data->ValueForSelectMenu--;
	}
	if (Input_GetKeyDown(VK_DOWN) && data->ValueForSelectMenu < 3)
	{
		data->ValueForSelectMenu++;
	}

	if (Input_GetKeyDown(VK_SPACE))
	{
		switch (data->ValueForSelectMenu)
		{
		case 1:
			Scene_SetNextScene(SCENE_MAIN);
			break;
		case 2:
			Scene_SetNextScene(SCENE_CREDIT);
			break;
		case 3:
			//Exit															//EXIT 구현 요. 선택시 한번 더 확인할건지??그냥 끌건지.
			break;
		}
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->Title_BackGroundImage, 0, 0);
	Renderer_DrawImage(&data->Title_BigTitle, 590, );
	
	//Position_X, Y 수정 요.
	if (data->TitleScenePlayTime >= 6)
	{
		Renderer_DrawImage(&data->BGImage, 0, 0);
		Renderer_DrawImage(&data->MainTitle, 0, 0);
		Renderer_DrawImage(&data->GameStart, 0, 0);
		Renderer_DrawImage(&data->Credit, 0, 0);
		Renderer_DrawImage(&data->Exit, 0, 0);
	}


}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;


	SafeFree(data);
}
#pragma endregion

#pragma region MainScene
typedef struct MainSceneData
{
	int32	temp;
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

}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

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
//추가 바람 <<ㅇㅋ


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