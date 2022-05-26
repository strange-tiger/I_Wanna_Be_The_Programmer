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
	
	//Main Title 이미지 출력 및 좌표 계산을 위한 구조체
	Image	Title_SmallTitle;
	int32	Title_SmallTitle_posX;
	int32	Title_SmallTitle_posY;

	Image	Title_BigTitle;
	int32	Title_BigTitle_posX;
	int32	Title_BigTitle_posY;

	//Title 화면 하단 메뉴 출력을 위한 구조체
	Image	Title_PressStart;

	Image	Title_GameStart;
	Image	Title_GameStart2;

	Image	Title_Credit;
	Image	Title_Credit2;

	Image	Title_Exit;
	Image	Title_Exit2;

	Image	Title_Arrow;
	int32	Title_Arrow_posY;















	//Title Scene 시간 및 메뉴 선택 구현을 위한 구조체
	float	TitleScenePlayTime;
	int32	ChooseTitleMenu;

	Music	BGM;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
	//배경 및 좌측하단 URL
	Image_LoadImage(&data->Title_BackGroundImage, "TitleImage01_BackGroundImage.png");
	Image_LoadImage(&data->Title_URL, "TitleText03_URL.png");

	//Main Title
	Image_LoadImage(&data->Title_BigTitle, "TitleText02_BIG_TITLE.png");
	Image_LoadImage(&data->Title_SmallTitle, "TitleText02_SMALL_TITLE.png");

	//Title 화면 하단 선택 메뉴
	Image_LoadImage(&data->Title_PressStart, "TitleText03_PRESS_START.png");

	Image_LoadImage(&data->Title_GameStart, "TitleText04_GAME_START_01.png");
	Image_LoadImage(&data->Title_GameStart2, "TitleText04_GAME_START_02.png");

	Image_LoadImage(&data->Title_Credit, "TitleText05_CREDIT_01.png");
	Image_LoadImage(&data->Title_Credit2, "TitleText05_CREDIT_02.png");

	Image_LoadImage(&data->Title_Exit, "TitleText06_EXIT_01.png");
	Image_LoadImage(&data->Title_Exit2, "TitleText06_EXIT_02.png");

	Image_LoadImage(&data->Title_Arrow, "TitleText07_ARROW.png");

	data->Title_BigTitle_posX = 110;
	data->Title_SmallTitle_posX = 367;
	data->Title_SmallTitle_posY = 15;	
	data->Title_BigTitle_posY = data->Title_SmallTitle_posY + 80;

	data->ChooseTitleMenu = 0;
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->TitleScenePlayTime += Timer_GetDeltaTime();

	//타이틀 화면 조작부
	if (Input_GetKeyDown(VK_UP) && data->ChooseTitleMenu > 1 )
	{
		data->ChooseTitleMenu--;
	}
	if (Input_GetKeyDown(VK_DOWN) && data->ChooseTitleMenu < 3)
	{
		data->ChooseTitleMenu++;
	}
	if (Input_GetKeyDown(VK_SPACE))
	{
		switch (data->ChooseTitleMenu)
		{
		case 0:
			data->ChooseTitleMenu = 1;
			break;
		case 1:
			Scene_SetNextScene(SCENE_MAIN);
			break;
		case 2:
			Scene_SetNextScene(SCENE_CREDIT);
			break;
		case 3:
			exit(0);															
			break;
		}
		
	}

	//일정 시간마다 Main Title 줌 인/아웃 구현을 위한 코오오오드
	if ((int32)(data->TitleScenePlayTime * 2.5) % 2 == 1)
	{
		data->Title_BigTitle.ScaleY -= 0.005f;
		data->Title_BigTitle.ScaleX -= 0.005f;

		data->Title_SmallTitle.ScaleY -= 0.005f;
		data->Title_SmallTitle.ScaleX -= 0.005f;
		
		data->Title_BigTitle_posX += 2;
		data->Title_BigTitle_posY++;
		
		data->Title_SmallTitle_posX += 1;
		data->Title_SmallTitle_posY++;
		
	}
	if ((int32)(data->TitleScenePlayTime * 2.5) % 2 == 0)
	{
		data->Title_SmallTitle.ScaleY += 0.005f;
		data->Title_SmallTitle.ScaleX += 0.005f;
		
		data->Title_BigTitle.ScaleY += 0.005f;
		data->Title_BigTitle.ScaleX += 0.005f;
		
		data->Title_BigTitle_posX -= 2;
		data->Title_BigTitle_posY--;
		
		data->Title_SmallTitle_posX -= 1;
		data->Title_SmallTitle_posY--;
	}
}


void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->Title_BackGroundImage, 0, 0);
	Renderer_DrawImage(&data->Title_URL, 5, 700);

	// Press Strat ☆반짝반짝☆
	if (data->ChooseTitleMenu == 0)
	{
		if ((int32)(data->TitleScenePlayTime * 10) % 2 == 1) 
		{
			Renderer_DrawImage(&data->Title_PressStart, 482, 600);
		}
	}
	if (data->ChooseTitleMenu != 0)
	{
		switch (data->ChooseTitleMenu)
		{
		case 1:
			Renderer_DrawImage(&data->Title_GameStart2, 316, 340);
			Renderer_DrawImage(&data->Title_Credit, 496, 460);
			Renderer_DrawImage(&data->Title_Exit, 513, 580);
			Renderer_DrawImage(&data->Title_Arrow, 603, 290);
			break;
		case 2:
			Renderer_DrawImage(&data->Title_GameStart, 368, 340);
			Renderer_DrawImage(&data->Title_Credit2, 422, 460);
			Renderer_DrawImage(&data->Title_Exit, 513, 580);
			Renderer_DrawImage(&data->Title_Arrow, 603, 400);
			break;
		case 3:
			Renderer_DrawImage(&data->Title_GameStart, 368, 340);
			Renderer_DrawImage(&data->Title_Credit, 496, 460);
			Renderer_DrawImage(&data->Title_Exit2, 473, 580);
			Renderer_DrawImage(&data->Title_Arrow, 603, 510);
			break;
		}
	}
	Renderer_DrawImage(&data->Title_BigTitle, data->Title_BigTitle_posX, data->Title_BigTitle_posY);
	Renderer_DrawImage(&data->Title_SmallTitle, data->Title_SmallTitle_posX, data->Title_SmallTitle_posY);
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
	Image_FreeImage(&data->Title_BackGroundImage);
	Image_FreeImage(&data->Title_URL);
	Image_FreeImage(&data->Title_SmallTitle);
	Image_FreeImage(&data->Title_BigTitle);
	Image_FreeImage(&data->Title_PressStart);
	Image_FreeImage(&data->Title_GameStart);
	Image_FreeImage(&data->Title_GameStart2);
	Image_FreeImage(&data->Title_Credit);
	Image_FreeImage(&data->Title_Credit2);
	Image_FreeImage(&data->Title_Exit);
	Image_FreeImage(&data->Title_Exit2);
	Image_FreeImage(&data->Title_Arrow);
	
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

typedef struct CreditSceneData
{
	Image	Credit_BackGroundImage;

	//순서대로 중재, 서연, 진호, 혁진, 재성, 우진, 재민의 사진 출력을 위한 구조체
	Image	Credit_Image_JJ;
	Image	Credit_Text_JJ;

	Image	Credit_Image_SY;
	Image	Credit_Text_SY;

	Image	Credit_Image_JH;
	Image	Credit_Text_JH;

	Image	Credit_Image_HJ;
	Image	Credit_Text_HJ;

	Image	Credit_Image_JS;
	Image	Credit_Text_JS;

	Image	Credit_Image_WJ;
	Image	Credit_Text_WJ;

	Image	Credit_Image_JM;
	Image	Credit_Text_JM;

	int32	Credit_Alpha;
	int32	CreditSceneChange;
	float	CreditScenePlayTime; 

	Music	BGM;
} CreditSceneData;

void init_Credit(void)
{
	g_Scene.Data = malloc(sizeof(CreditSceneData));
	memset(g_Scene.Data, 0, sizeof(CreditSceneData));

	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	//Image File Load
	Image_LoadImage(&data->Credit_BackGroundImage, "Credit_BackGroundImage.png");
	
	Image_LoadImage(&data->Credit_Image_JJ, "Credit_Image_JJ.jpeg");
	Image_LoadImage(&data->Credit_Text_JJ, "Credit_Text_JJ.png");
	
	Image_LoadImage(&data->Credit_Image_SY, "Credit_Image_SY.png");
	Image_LoadImage(&data->Credit_Text_SY, "Credit_Text_SY.png");
	
	Image_LoadImage(&data->Credit_Image_JH, "Credit_Image_JH.jpg");
	Image_LoadImage(&data->Credit_Text_JH, "Credit_Text_JH.png");
	
	Image_LoadImage(&data->Credit_Image_HJ, "Credit_Image_HJ.jpg");
	Image_LoadImage(&data->Credit_Text_HJ, "Credit_Text_HJ.png");
	
	Image_LoadImage(&data->Credit_Image_JS, "Credit_Image_JS.png");
	Image_LoadImage(&data->Credit_Text_JS, "Credit_Text_JS.png");
	
	Image_LoadImage(&data->Credit_Image_WJ, "Credit_Image_WJ.jpg");
	Image_LoadImage(&data->Credit_Text_WJ, "Credit_Text_WJ.png");
	
	Image_LoadImage(&data->Credit_Image_JM, "Credit_Image_JM.jpeg");
	Image_LoadImage(&data->Credit_Text_JM, "Credit_Text_JM.png");

	data->CreditSceneChange = 1;

	//크레딧 이미지 전체 초기 알파값 Min으로 지정
	data->Credit_Alpha = Clamp(0, data->Credit_Alpha - 255, 255);
}

void update_Credit(void)
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;
	data->CreditScenePlayTime += Timer_GetDeltaTime();

	//스페이스바를 누르거나 누적 델타타임이 7초를 넘으면 카운트를 +1 시킬 것이에요
	if (Input_GetKeyDown(VK_SPACE) || data->CreditScenePlayTime > 7.0)
	{
		data->CreditSceneChange++;
		data->CreditScenePlayTime = 0.0f;
	}

	//카운트가 8이 되면 타이틀로 이동하세용
	if (data->CreditSceneChange == 8)
	{
		Scene_SetNextScene(SCENE_TITLE);
		data->CreditSceneChange = 0;
	}

	//지정 시간마다 페이드 인/아웃 효과를 주세용
	if (0.5 <= data->CreditScenePlayTime && data->CreditScenePlayTime < 1)
	{
		data->Credit_Alpha = Clamp(0, data->Credit_Alpha + 10, 255);
	}
	if (6 <= data->CreditScenePlayTime && data->CreditScenePlayTime < 6.5)
	{
		data->Credit_Alpha = Clamp(0, data->Credit_Alpha - 10, 255);
	}
	Image_SetAlphaValue(&data->Credit_Image_JJ, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Image_SY, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Image_JH, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Image_HJ, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Image_JS, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Image_WJ, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Image_JM, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Text_JJ, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Text_SY, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Text_JH, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Text_HJ, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Text_JS, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Text_WJ, data->Credit_Alpha);
	Image_SetAlphaValue(&data->Credit_Text_JM, data->Credit_Alpha);
}


void render_Credit(void)
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->Credit_BackGroundImage, 0, 0);

	switch (data->CreditSceneChange)
	{
	case 1:
		Renderer_DrawImage(&data->Credit_Image_JJ, 0, 0);
		Renderer_DrawImage(&data->Credit_Text_JJ, 0, 0);
		break;
	case 2:
		Renderer_DrawImage(&data->Credit_Image_SY, 0, 0);
		Renderer_DrawImage(&data->Credit_Text_SY, 0, 0);
		break;
	case 3:
		Renderer_DrawImage(&data->Credit_Image_JH, 0, 0);
		Renderer_DrawImage(&data->Credit_Text_JH, 0, 0);
		break;
	case 4:
		Renderer_DrawImage(&data->Credit_Image_HJ, 0, 0);
		Renderer_DrawImage(&data->Credit_Text_HJ, 0, 0);
		break;
	case 5:
		Renderer_DrawImage(&data->Credit_Image_JS, 0, 0);
		Renderer_DrawImage(&data->Credit_Text_JS, 0, 0);
		break;
	case 6:
		Renderer_DrawImage(&data->Credit_Image_JM, 0, 0);
		Renderer_DrawImage(&data->Credit_Text_JM, 0, 0);
		break;
	case 7:
		Renderer_DrawImage(&data->Credit_Image_WJ, 0, 0);
		Renderer_DrawImage(&data->Credit_Text_WJ, 0, 0);
		break;
	}
}

void release_Credit(void)
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	Image_FreeImage(&data->Credit_BackGroundImage);
	Image_FreeImage(&data->Credit_Image_JJ);
	Image_FreeImage(&data->Credit_Text_JJ);
	Image_FreeImage(&data->Credit_Image_SY);
	Image_FreeImage(&data->Credit_Text_SY);
	Image_FreeImage(&data->Credit_Image_JH);
	Image_FreeImage(&data->Credit_Text_JH);
	Image_FreeImage(&data->Credit_Image_HJ);
	Image_FreeImage(&data->Credit_Text_HJ);
	Image_FreeImage(&data->Credit_Image_JS);
	Image_FreeImage(&data->Credit_Text_JS);
	Image_FreeImage(&data->Credit_Image_WJ);
	Image_FreeImage(&data->Credit_Text_WJ);
	Image_FreeImage(&data->Credit_Image_JM);
	Image_FreeImage(&data->Credit_Text_JM);

	SafeFree(data);
}

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
		g_Scene.Init = init_Credit;
		g_Scene.Update = update_Credit;
		g_Scene.Render = render_Credit;
		g_Scene.Release = release_Credit;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}

bool Scene_IsGameClose(void) {
	return s_isGameClose;
}