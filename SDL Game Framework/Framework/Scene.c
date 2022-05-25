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
	L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
	L"B키를 누르면 폰트가 굵게 변합니다.",
	L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
	L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
	L"S키를 누르면 텍스트에 취소선이 생깁니다.",
	L"N키를 누르면 다시 원래대로 돌아옵니다.",
	L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
	L"1키를 누르면 텍스트가 작아집니다.",
	L"2키를 누르면 텍스트가 커집니다.",
	L"스페이스 키를 누르면 다음 씬으로 넘어갑니다."
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
	int32	Block_X;					//블록 프린트 시작점 좌표
	int32	Block_Y;
	int32	Block_Polygon_X;
	int32	Block_Polygon_Y;			//블록 폴리곤 개념 좌표


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

float JumpTime = 0.0f;			//점프 구현방식 : 위 화살표 누르면 일정 시간동안 Y좌표 --;
int32 Jump = 0;					//현재 케릭터가 점프중인지 표시하는 변수, 후에 모어점핑 구현을 위한 변수로 사용 가능.
float AttackTime = 0.0f;		//공격 이펙트 표현을 위해 델타타임 누적받을 변수
int32 Attack = 0;				
int32 Character_Direction = 1;	//케릭터 방향 표현을 위해 임시로 썼음.(Left / Right)
int32 EnemyHP = 100;			//몬스터 HP 초기설정.

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->EnemyHPgauge_X = data->Enemy_X;
	data->EnemyHPgauge_Y = data->Enemy_Y + 350;
	data->EnemyHPgaugeValue.ScaleX = (float)EnemyHP / 100;		//스케일조정으로 몬스터 체력바 조정

	data->Block_Polygon_X = data->Block_X + 80;
	data->Block_Polygon_Y = data->Block_Y + 80;					//폴리곤 개념으로 블럭의 크기를 설정하려 했으나 아무리 생각해도 내가 멍청이인것같음
	data->Character_Polygon_X = data->Character_X + 100;
	data->Character_Polygon_Y = data->Character_Y + 100;


	/*  벽 없이 몬스터만 있을때 쓰던 케릭터 이동 코드
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

	//현재 쓰는 이동 코드.
	//케릭터의 좌표가 블럭 폴리곤 밖에 있을때만 이동 가능. X축만 구현해 놓은 상황이다 보니 사실상 화면 전체에 투명 벽이 하나 있는 모양이 됐음.
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

	//난 멍청이야ㅠㅠ
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

	//몬스터의 좌표 기준 일정 범위 내에서만 공격이 들어감. 이번 게임에서는 지워도 상관음슴
	//본격적으로 게임 내에서는 스페이스바를 점프키로 쓸 계획.
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
		
		//몬스터의 HP가 0이면 출력 안행
		if (EnemyHP > 0)
		{
			Renderer_DrawImage(&data->Enemy, data->Enemy_X, data->Enemy_Y);
		}
		Renderer_DrawImage(&data->Effect, data->Effect_X, data->Effect_Y);

		Renderer_DrawImage(&data->Block, data->Block_X, data->Block_Y);
		Renderer_DrawImage(&data->EnemyHPgaugeBack, data->EnemyHPgauge_X, data->EnemyHPgauge_Y);
		Renderer_DrawImage(&data->EnemyHPgaugeValue, data->EnemyHPgauge_X, data->EnemyHPgauge_Y);
		//이미지 렌더링을 위한 코오오오드
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
	L"여기서는 사운드와 이미지 블렌딩에 대해서 알아봅시다.",
	L"화살표키로 이미지를 이동시킬 수 있습니다.",
	L"E키를 누르면 이펙트를 재생시킬 수 있습니다. 이펙트 소리가 작으니 볼륨을 낮춘 후 진행하세요.",
	L"M키로 음악을 끄거나 켤 수 있습니다.",
	L"P키로 음악을 멈추거나 재개할 수 있습니다.",
	L"1번과 2번으로 볼륨을 조절할 수 있습니다.",
	L"WASD로 이미지의 스케일을 조정할 수 있습니다.",
	L"KL키로 이미지의 투명도를 조절할 수 있습니다."
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