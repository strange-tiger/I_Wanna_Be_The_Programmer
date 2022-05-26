#include "Map.h"
#include "Trap.h"

void Map_Init(Map* map, int32 StageNum)
{
	// 테스트용
	//CsvFile* csvFile;
	//CreateCsvFile(csvFile, "CsvTest.csv");

	Image_LoadImage(&map->BackGroundImage, "");
	Audio_LoadMusic(&map->BGM, "");
	Audio_LoadMusic(&map->DieBGM, "");

	//맵 시작 지점 좌표 초기화
	map->StartPoint.X = 0;
	map->StartPoint.Y = 0;

	//맵 목적 지점 좌표 초기화
	map->DestinationPoint.X = 0;
	map->DestinationPoint.Y = 0;

	//델타타임 저장 초기화
	map->ActiveTime = 0.0f;

	for (int i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		Image_LoadImage(&map->PlatformList[i].Image, "");			// Platform 이미지 로드 // csv 파싱 값

		// 좌표 및 가로세로 폭 초기화 // csv 파싱 값
		map->PlatformList[i].Position.X = 0;
		int32 platformX = map->PlatformList[i].Position.X;

		map->PlatformList[i].Position.Y = 0;
		int32 platformY = map->PlatformList[i].Position.Y;

		map->PlatformList[i].Width = 0;
		int32 platformWidth = map->PlatformList[i].Width;

		map->PlatformList[i].Height = 0;
		int32 platformHeight = map->PlatformList[i].Height;

		// Platform Rect 구성
		map->PlatformList[i].Rect.left		= platformX - platformWidth / 2;
		map->PlatformList[i].Rect.top		= platformY - platformHeight / 2;
		map->PlatformList[i].Rect.right		= platformX + platformWidth / 2;
		map->PlatformList[i].Rect.bottom	= platformY + platformHeight / 2;
	}

	for (int i = 0; i < MAX_TRAP_COUNT; i++)
	{
		Image_LoadImage(&map->TrapList[i].Image, "");				// Trap 이미지 로드 // csv 파싱 값
		
		// 좌표 및 가로세로 폭 초기화 // csv 파싱 값
		map->TrapList[i].Position.X = 0;
		int32 trapX = map->TrapList[i].Position.X;

		map->TrapList[i].Position.Y = 0;
		int32 trapY = map->TrapList[i].Position.Y;

		map->TrapList[i].Width = 0;
		int32 trapWidth = map->TrapList[i].Width;

		map->TrapList[i].Height = 0;
		int32 trapHeight = map->TrapList[i].Height;

		// Trap Rect 구성
		map->TrapList[i].Rect.left			= trapX - trapWidth / 2;
		map->TrapList[i].Rect.top			= trapY - trapHeight / 2;
		map->TrapList[i].Rect.right			= trapX + trapWidth / 2;
		map->TrapList[i].Rect.bottom		= trapY + trapHeight / 2;

		map->TrapList[i].Type = TRAP_BASIC;							// Trap 타입 초기화 // csv 파싱 값
		map->TrapList[i].TargetPosition.X = 0;							// Trap 타겟 위치 X 초기화 // 직선 or 플레이어 위치
		map->TrapList[i].TargetPosition.Y = 0;							// Trap 타겟 위치 Y 초기화 // 직선 or 플레이어 위치

		map->TrapList[i].ImageAlpha = 255;							// ImageAlpha 초기화 // csv 파싱 값

		Audio_LoadSoundEffect(&map->TrapList[i].effectSound, "");	// Trap 오디오 로드 // csv 파싱 값
		Image_LoadImage(&map->TrapList[i].Image2, "");				// Trap 변경용 이미지 로드 // csv 파싱 값
	}

	for (int i = 0; i < MAX_SAVE_POINT_COUNT; i++)
	{
		Image_LoadImage(&map->SavePointList[i].Platform.Image, "");			// SavePoint 이미지 로드 // csv 파싱 값

		// 좌표 및 가로세로 폭 초기화 // csv 파싱 값
		map->SavePointList[i].Platform.Position.X = 0;
		int32 platformX = map->SavePointList[i].Platform.Position.X;

		map->SavePointList[i].Platform.Position.Y = 0;
		int32 platformY = map->SavePointList[i].Platform.Position.Y;

		map->SavePointList[i].Platform.Width = 0;
		int32 platformWidth = map->SavePointList[i].Platform.Width;

		map->SavePointList[i].Platform.Height = 0;
		int32 platformHeight = map->SavePointList[i].Platform.Height;

		// Platform Rect 구성
		map->SavePointList[i].Platform.Rect.left = platformX - platformWidth / 2;
		map->SavePointList[i].Platform.Rect.top = platformY - platformHeight / 2;
		map->SavePointList[i].Platform.Rect.right = platformX + platformWidth / 2;
		map->SavePointList[i].Platform.Rect.bottom = platformY + platformHeight / 2;

		map->SavePointList[i].Active = false;		//SavePoint 활성도 초기화
	}
}

void Map_Update(Map* map, Player* player)	// player 정보도 들어가는 것이 맞나..?
{
	map->ActiveTime += Timer_GetDeltaTime();
	for (int32 i = 0; i < MAX_TRAP_COUNT; i++)
	{
		map->TrapList[i].ActiveTime = map->ActiveTime;
	}

	for (int32 i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		switch (map->PlatformList[i].Move)
		{
		case 0:
			break;
		case 1:
			Platform_PlatformHorizontalMove(map, &map->PlatformList[i]);
			break;
		case 2:
			Platform_PlatformVerticalMove(map, &map->PlatformList[i]);
			break;
		default:
			break;
		}
	}

	for (int32 i = 0; i < MAX_TRAP_COUNT; i++)
	{
		Trap_TrapMove(&map->TrapList[i], player, x, y);		//x, y는 csv로 파싱
		Trap_TrapSwitch(&map->TrapList[i]);
	}

	if (map->ActiveTime > PLATFORM_MOVE_CYCLE)
	{
		map->ActiveTime = 0.0f;
	}

	Map_DetectSavePoint(map, player);

	for (int32 i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		bool IsGround;										//나중에 Player와 연결
		IsGround = Platform_DetectIsGround(&map->PlatformList[i], player);
	}

}

void Map_Render(Map* map)
{
	Renderer_DrawImage(&map->BackGroundImage, 0, 0);

	for (int i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		Renderer_DrawImage(&map->PlatformList[i].Image, &map->PlatformList[i].Position.X, &map->PlatformList[i].Position.Y);
	}

	for (int i = 0; i < MAX_TRAP_COUNT; i++)
	{
		Renderer_DrawImage(&map->TrapList[i].Image, &map->TrapList[i].Position.X, &map->TrapList[i].Position.Y);
	}
}

void Map_Release(Map* map)
{
	Image_FreeImage(&map->BackGroundImage);
	Audio_FreeMusic(&map->BGM);
	Audio_FreeMusic(&map->DieBGM);

	for (int i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		Image_FreeImage(&map->PlatformList[i].Image);
	}

	for (int i = 0; i < MAX_TRAP_COUNT; i++)
	{
		Image_FreeImage(&map->TrapList[i].Image);
		Audio_FreeSoundEffect(&map->TrapList[i].effectSound);
	}
}

bool Platform_DetectIsGround(Platform* platform, Player* player)
{
	RECT tempRect;
	
	if (player->Rect.left > platform->Rect.right || player->Rect.right < platform->Rect.left)
	{
		return false;
	}
	else if (player->Rect.bottom <= platform->Rect.top /*IntersectRect(&tempRect, &player->Rect, &platform->Rect)*/)
	{
		return true;
	}

	return false;
	
}

void Platform_PlatformHorizontalMove(Map* map, Platform* platform)
{
	if (map->ActiveTime >= PLATFORM_MOVE_CYCLE)
	{
		if (!platform->Direction)
		{
			platform->Position.X += PLATFORM_MOVE_SPEED;
		}
		else if (platform->Direction)
		{
			platform->Position.X -= PLATFORM_MOVE_SPEED;
		}
		map->ActiveTime = 0.0f;
		platform->Direction = !platform->Direction;
	}
}

void Platform_PlatformVerticalMove(Map* map, Platform* platform)
{
	if (map->ActiveTime >= PLATFORM_MOVE_CYCLE)
	{
		if (!platform->Direction)
		{
			platform->Position.Y += PLATFORM_MOVE_SPEED;
		}
		else if (platform->Direction)
		{
			platform->Position.Y -= PLATFORM_MOVE_SPEED;
		}
		map->ActiveTime = 0.0f;
		platform->Direction = !platform->Direction;
	}
}

void Map_DetectSavePoint(Map* map, Player* player)
{
	RECT tempRect;

	for (int i = 0; i < MAX_SAVE_POINT_COUNT; i++)
	{
		if (map->SavePointList[i].Active == false)
		{
			if (IntersectRect(&tempRect, &player->Rect, &map->SavePointList[i].Platform.Rect)) // 플레이어와 세이브 포인트 충돌 처리
			{
				map->SavePointList[i].Active = !map->SavePointList[i].Active;

				map->RespawnPoint = map->SavePointList[i].Platform.Position;
			}
		}
	}
}
