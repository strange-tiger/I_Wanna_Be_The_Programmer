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

	Text_CreateText(&data->mainText, "d2coding.ttf", 40, L"�̰Ž� Ÿ��Ʋ", wcslen(L"�̰Ž� Ÿ��Ʋ"));
	Text_CreateText(&data->NextText, "d2coding.ttf", 40, L"Space ���� ���� ������", wcslen(L"Space ���� ���� ������"));
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
	Renderer_DrawTextShaded(&data->mainText, 0, 0, bgColor, textColor);
	Renderer_DrawTextShaded(&data->NextText, 0, 0, bgColor, textColor);
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Text_FreeText(&data->mainText);
	Text_FreeText(&data->NextText);

	SafeFree(g_Scene.Data);
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