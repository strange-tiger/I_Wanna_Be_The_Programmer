#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"
#include "Framework/Csv.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"����� Ÿ��Ʋ���Դϴ�. �ؽ�Ʈ�� ���õ� ���������� �׽�Ʈ�غ��ô�.",
	L"BŰ�� ������ ��Ʈ�� ���� ���մϴ�.",
	L"IŰ�� ������ ��Ʈ�� ���Ÿ�ü�� ���մϴ�.",
	L"UŰ�� ������ �ؽ�Ʈ�� ������ ����ϴ�.",
	L"SŰ�� ������ �ؽ�Ʈ�� ��Ҽ��� ����ϴ�.",
	L"NŰ�� ������ �ٽ� ������� ���ƿɴϴ�.",
	L"CŰ�� ������ ���� ��尡 �ٲ�ϴ�. (Solid -> Shaded -> Blended)",
	L"1Ű�� ������ �ؽ�Ʈ�� �۾����ϴ�.",
	L"2Ű�� ������ �ؽ�Ʈ�� Ŀ���ϴ�.",
	L"�����̽� Ű�� ������ ���� ������ �Ѿ�ϴ�."
};

typedef struct TitleSceneData
{
	Text	GuideLine[10];
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
	Image	Map;
	Image	Character;
	int32	Character_Alpha;

	int32	Alpha;
	int32	Character_X;
	int32	Character_Y;
	int32	Character_Polygon_X;
	int32	Character_Polygon_Y;

	int32	Effect_Alpha;
	Image	Effect;
	int32	Effect_X;
	int32	Effect_Y;

	Image	Enemy;
	int32	Enemy_X;
	int32	Enemy_Y;

	Image	Block;
	int32	Block_Alpha;
	int32	Block_X;					//��� ����Ʈ ������ ��ǥ
	int32	Block_Y;
	int32	Block_Polygon_X;
	int32	Block_Polygon_Y;			//��� ������ ���� ��ǥ


	Image	EnemyHPgaugeBack;
	Image	EnemyHPgaugeValue;
	int32	EnemyHPgauge_X;
	int32	EnemyHPgauge_Y;


} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;



	data->RenderMode = SOLID;

	Image_LoadImage(&data->Map, "map.png");
	Image_LoadImage(&data->Character, "character.png");
	Image_LoadImage(&data->Effect, "Effect.png");
	Image_LoadImage(&data->Enemy, "Enemy.png");
	Image_LoadImage(&data->EnemyHPgaugeBack, "EnemyHPgaugeBack.png");
	Image_LoadImage(&data->EnemyHPgaugeValue, "EnemyHPgaugeValue.png");
	Image_LoadImage(&data->Block, "Block.png");
	data->Character_X = 100;
	data->Character_Y = 430;
	data->Enemy_X = 700;
	data->Enemy_Y = 300;
	data->Block_X = 500;
	data->Block_Y = 430;
}

float JumpTime = 0.0f;			//���� ������� : �� ȭ��ǥ ������ ���� �ð����� Y��ǥ --;
int32 Jump = 0;					//���� �ɸ��Ͱ� ���������� ǥ���ϴ� ����, �Ŀ� ������� ������ ���� ������ ��� ����.
float AttackTime = 0.0f;		//���� ����Ʈ ǥ���� ���� ��ŸŸ�� �������� ����
int32 Attack = 0;				
int32 Character_Direction = 1;	//�ɸ��� ���� ǥ���� ���� �ӽ÷� ����.(Left / Right)
int32 EnemyHP = 100;			//���� HP �ʱ⼳��.

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->EnemyHPgauge_X = data->Enemy_X;
	data->EnemyHPgauge_Y = data->Enemy_Y + 350;
	data->EnemyHPgaugeValue.ScaleX = (float)EnemyHP / 100;		//�������������� ���� ü�¹� ����

	data->Block_Polygon_X = data->Block_X + 80;
	data->Block_Polygon_Y = data->Block_Y + 80;					//������ �������� ���� ũ�⸦ �����Ϸ� ������ �ƹ��� �����ص� ���� ��û���ΰͰ���
	data->Character_Polygon_X = data->Character_X + 100;
	data->Character_Polygon_Y = data->Character_Y + 100;


	/*  �� ���� ���͸� ������ ���� �ɸ��� �̵� �ڵ�
	if (Input_GetKey(VK_LEFT) && data->Character_X >= 15)
	{
		data->Character_X -= 15;
		Character_Direction = 0;
	}

	if (Input_GetKey(VK_RIGHT) && data->Character_X <= 1200)
	{
		data->Character_X += 15;
		Character_Direction = 1;
	}
	*/

	//���� ���� �̵� �ڵ�.
	//�ɸ����� ��ǥ�� �� ������ �ۿ� �������� �̵� ����. X�ุ ������ ���� ��Ȳ�̴� ���� ��ǻ� ȭ�� ��ü�� ���� ���� �ϳ� �ִ� ����� ����.
	if (Input_GetKeyDown(VK_UP))
	{
		Jump = 1;
	}
	if(Input_GetKey(VK_LEFT))
	{
		if(data->Character_Polygon_X <= data->Block_X  + 15 || data->Block_Polygon_X <= data->Character_X)
		{
			data->Character_X -= 15;
			Character_Direction = 0;
		}
	}
	
	if (Input_GetKey(VK_RIGHT))
	{
		if (data->Character_Polygon_X <= data->Block_X || data->Block_Polygon_X - 15 <= data->Character_X)
		{
			data->Character_X += 15;
				Character_Direction = 0;
		}
	}

	//�� ��û�̾ߤФ�
	if (Jump == 1)
	{
		JumpTime += Timer_GetDeltaTime();
		if (JumpTime <= 0.1)
		{
			data->Character_Y -= 30;

		}
		if (JumpTime > 0.1)
		{
			JumpTime = 0.0f;
			Jump = 0;
		}
	}

	if (data->Character_Y < 430 && Jump == 0)
	{
		data->Character_Y += 30;
	}

	if (Input_GetKey(VK_DOWN))
	{
		
	}

	if (Character_Direction == 1)
	{
		data->Effect_X = data->Character_X + 80;
		data->Effect_Y = data->Character_Y + 10;
	}
	if (Character_Direction == 0)
	{
		data->Effect_X = data->Character_X - 20;
		data->Effect_Y = data->Character_Y + 10;
	}

	//������ ��ǥ ���� ���� ���� �������� ������ ��. �̹� ���ӿ����� ������ �������
	//���������� ���� �������� �����̽��ٸ� ����Ű�� �� ��ȹ.
	if (Input_GetKeyDown(VK_SPACE))
	{
		Attack = 1;
		if (data->Enemy_X - data->Character_X < 100)
		{
			if (data->Enemy_Y - data->Character_Y < 100)
			{
			
				EnemyHP -= 10;
			}
		}
	}
	else
	{
		data->Character_Alpha = Clamp(0, data->Character_Alpha + 255, 255);
	}
	if (Attack == 1)
	{
		AttackTime += Timer_GetDeltaTime();
		data->Effect_Alpha = Clamp(0, data->Effect_Alpha + 30, 255);
		if (AttackTime > 0.5)
		{

			Attack = 0;
		}
	}
	if (Attack == 0)
	{
		data->Effect_Alpha = Clamp(0, data->Effect_Alpha - 30, 255);
		AttackTime = 0.0f;

	}

	data->Alpha = Clamp(0, data->Alpha + 255, 255);
	Image_SetAlphaValue(&data->Character, data->Character_Alpha);
	Image_SetAlphaValue(&data->Effect, data->Effect_Alpha);
	Image_SetAlphaValue(&data->Block, data->Alpha);
	Image_SetAlphaValue(&data->Map, data->Alpha);


}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;


		
		Renderer_DrawImage(&data->Map, 0, 0);
		Renderer_DrawImage(&data->Character, data->Character_X, data->Character_Y);
		
		//������ HP�� 0�̸� ��� ����
		if (EnemyHP > 0)
		{
			Renderer_DrawImage(&data->Enemy, data->Enemy_X, data->Enemy_Y);
		}
		Renderer_DrawImage(&data->Effect, data->Effect_X, data->Effect_Y);

		Renderer_DrawImage(&data->Block, data->Block_X, data->Block_Y);
		Renderer_DrawImage(&data->EnemyHPgaugeBack, data->EnemyHPgauge_X, data->EnemyHPgauge_Y);
		Renderer_DrawImage(&data->EnemyHPgaugeValue, data->EnemyHPgauge_X, data->EnemyHPgauge_Y);
		//�̹��� �������� ���� �ڿ�������
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->TestText);

	Image_FreeImage(&data->Map);
	Image_FreeImage(&data->Character);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region MainScene
const wchar_t* str2[] = {
	L"���⼭�� ����� �̹��� ������ ���ؼ� �˾ƺ��ô�.",
	L"ȭ��ǥŰ�� �̹����� �̵���ų �� �ֽ��ϴ�.",
	L"EŰ�� ������ ����Ʈ�� �����ų �� �ֽ��ϴ�. ����Ʈ �Ҹ��� ������ ������ ���� �� �����ϼ���.",
	L"MŰ�� ������ ���ų� �� �� �ֽ��ϴ�.",
	L"PŰ�� ������ ���߰ų� �簳�� �� �ֽ��ϴ�.",
	L"1���� 2������ ������ ������ �� �ֽ��ϴ�.",
	L"WASD�� �̹����� �������� ������ �� �ֽ��ϴ�.",
	L"KLŰ�� �̹����� ������ ������ �� �ֽ��ϴ�."
};

#define GUIDELINE_COUNT 8

typedef struct MainSceneData
{
	Text		GuideLine[GUIDELINE_COUNT];
	Music		BGM;
	float		Volume;
	SoundEffect Effect;
	Image		BackGround;
	float		Speed;
	int32		X;
	int32		Y;
	int32		Alpha;
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

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str2[i], wcslen(str2[i]));
	}
	
	Image_LoadImage(&data->BackGround, "background.jfif");

	Audio_LoadMusic(&data->BGM, "powerful.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_LoadSoundEffect(&data->Effect, "effect2.wav");
	Audio_HookSoundEffectFinished(log2OnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;

	data->Speed = 400.0f;
	data->X = 400;
	data->Y = 400;
	data->Alpha = 255;
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('E'))
	{
		Audio_PlaySoundEffect(&data->Effect, 1);
	}

	if (Input_GetKeyDown('M'))
	{
		if (Audio_IsMusicPlaying())
		{
			Audio_Stop();
		}
		else
		{
			Audio_Play(&data->BGM, INFINITY_LOOP);
		}
	}

	if (Input_GetKeyDown('P'))
	{
		if (Audio_IsMusicPaused())
		{
			Audio_Resume();
		}
		else
		{
			Audio_Pause();
		}
	}

	if (Input_GetKey('1'))
	{
		data->Volume -= 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey('2'))
	{
		data->Volume += 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey(VK_DOWN))
	{
		data->Y += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_UP))
	{
		data->Y -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_LEFT))
	{
		data->X -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_RIGHT))
	{
		data->X += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey('W'))
	{
		data->BackGround.ScaleY -= 0.05f;
	}

	if (Input_GetKey('S'))
	{
		data->BackGround.ScaleY += 0.05f;
	}

	if (Input_GetKey('A'))
	{
		data->BackGround.ScaleX -= 0.05f;
	}

	if (Input_GetKey('D'))
	{
		data->BackGround.ScaleX += 0.05f;
	}

	if (Input_GetKey('K'))
	{
		data->Alpha = Clamp(0, data->Alpha - 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}

	if (Input_GetKey('L'))
	{
		data->Alpha = Clamp(0, data->Alpha + 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}

	Renderer_DrawImage(&data->BackGround, data->X, data->Y);
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Audio_FreeMusic(&data->BGM);
	Audio_FreeSoundEffect(&data->Effect);

	Image_FreeImage(&data->BackGround);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region PageScene

#include "Game/PageManager.h"

typedef struct PageSceneData
{
	PageManager PageManager;
} PageSceneData;

void init_page(void)
{
	g_Scene.Data = malloc(sizeof(PageSceneData));
	
	PageSceneData* data = (PageSceneData*)g_Scene.Data;
	memset(data, 0, sizeof(PageSceneData));

	PageManager_Init(&data->PageManager);
}

void update_page(void)
{
	PageSceneData* data = (PageSceneData*)g_Scene.Data;

	PageManager_Update(&data->PageManager);
}

void render_page(void)
{
	PageSceneData* data = (PageSceneData*)g_Scene.Data;

	PageManager_Render(&data->PageManager);
}

void release_page(void)
{
	PageSceneData* data = (PageSceneData*)g_Scene.Data;

	PageManager_Release(&data->PageManager);

	SafeFree(g_Scene.Data);
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
	case SCENE_PAGE:
		g_Scene.Init = init_page;
		g_Scene.Update = update_page;
		g_Scene.Render = render_page;
		g_Scene.Release = release_page;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}