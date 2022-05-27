#include "Map.h"
#include "Trap.h"

void Map_Init(Map* map, int32 StageNum)
{
	// 테스트용
	//CsvFile* csvFile;
	//CreateCsvFile(csvFile, "CsvTest.csv");

	Image_LoadImage(&map->BackGroundImage, "");			// 배경 이미지 로드
	Audio_LoadMusic(&map->BGM, "");						// 배경 음악 로드
	Audio_LoadMusic(&map->DieBGM, "");					// 사망시 음악 로드

	Image_LoadImage(&map->Radder.Platform.Image, "");	// Radder 이미지 로드
	map->Radder.Active = false;							// Radder 활성 초기화
	map->Radder.Event = NULL;							// Radder 이벤트 초기화

	//맵 시작 지점 좌표 초기화										/// csv파싱 필요
	map->StartPoint.X = 0;
	map->StartPoint.Y = 0;

	//맵 목적 지점 좌표 초기화										/// csv파싱 필요
	map->DestinationPoint.X = 0;
	map->DestinationPoint.Y = 0;

	//델타타임 저장 초기화
	map->ActiveTime = 0.0f;

	for (int i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		// Platform 이미지 로드
		Image_LoadImage(&map->PlatformList[i].Image, "");			/// csv파싱 필요

		// 좌표 및 가로세로 폭 초기화									/// csv파싱 필요
		map->PlatformList[i].Position.X = 0;
		map->PlatformList[i].Position.Y = 0;
		map->PlatformList[i].Width = 0;
		map->PlatformList[i].Height = 0;
				
		// Platform Rect 구성
		Platform_CreateRect(&map->PlatformList[i]);
	}

	for (int i = 0; i < MAX_TRAP_COUNT; i++)
	{
		// Trap 이미지 로드
		Image_LoadImage(&map->TrapList[i].Platform.Image, "");		/// csv파싱 필요
		// Trap 바꿀 이미지 로드 
		Image_LoadImage(&map->TrapList[i].Image2, "");				/// csv파싱 필요
		// Trap 오디오 로드
		Audio_LoadSoundEffect(&map->TrapList[i].effectSound, "");	/// csv파싱 필요
		
		// 좌표 및 가로세로 폭 초기화									/// csv파싱 필요
		map->TrapList[i].Platform.Position.X = 0;
		map->TrapList[i].Platform.Position.Y = 0;
		map->TrapList[i].Platform.Width = 0;
		map->TrapList[i].Platform.Height = 0;

		// Trap Rect 구성
		Platform_CreateRect(&map->TrapList[i].Platform);

		map->TrapList[i].Type = TRAP_BASIC;	// Trap 타입 초기화		/// csv파싱 필요

		map->TrapList[i].Active = true;		// Trap 활성화 초기화	/// csv파싱 필요
		map->TrapList[i].ActiveTime = 0.0f;	// Trap 델타타임 초기화	/// csv파싱 필요

		map->TrapList[i].TargetPosition.X = 0;	// Trap 타겟 위치 X 초기화 // 직선 or 플레이어 위치
		map->TrapList[i].TargetPosition.Y = 0;	// Trap 타겟 위치 Y 초기화 // 직선 or 플레이어 위치

		map->TrapList[i].ImageAlpha = 255;	// ImageAlpha 초기화		/// 변경 시 csv파싱 여부 확인 요
	}

	for (int i = 0; i < MAX_SAVE_POINT_COUNT; i++)
	{
		// SavePoint 이미지 로드
		Image_LoadImage(&map->SavePointList[i].Platform.Image, "");	/// csv파싱 필요

		// 좌표 및 가로세로 폭 초기화									/// csv파싱 필요
		map->SavePointList[i].Platform.Position.X = 0;
		map->SavePointList[i].Platform.Position.Y = 0;
		map->SavePointList[i].Platform.Width = 0;
		map->SavePointList[i].Platform.Height = 0;

		// Platform Rect 구성
		Platform_CreateRect(&map->SavePointList[i].Platform);

		map->SavePointList[i].Active = false;			//SavePoint 활성도 초기화
	}

	for (int i = 0; i < MAX_SWITCH_COUNT; i++)
	{
		//Image_LoadImage(&map->SwitchList[i].Platform.Image, "");			// Switch 이미지 로드 // csv 파싱 값 // 필요없을 거라 예상

		// 좌표 및 가로세로 폭 초기화									/// csv파싱 필요
		map->SwitchList[i].Platform.Position.X = 0;
		map->SwitchList[i].Platform.Position.Y = 0;
		map->SwitchList[i].Platform.Width = 0;
		map->SwitchList[i].Platform.Height = 0;

		// Platform Rect 구성
		Platform_CreateRect(&map->SwitchList[i].Platform);

		map->SwitchList[i].Active = false;				//SavePoint 활성도 초기화

		map->SwitchList[i].Event = NULL;
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
		switch (map->PlatformList[i].MoveState)
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
		Trap_TrapMove(&map->TrapList[i], player, x, y);				/// csv파싱 필요
		Trap_TrapSwitch(&map->TrapList[i]);
	}

	if (map->ActiveTime > PLATFORM_MOVE_CYCLE)
	{
		map->ActiveTime = 0.0f;
	}

	Map_DetectSavePoint(map, player);

	for (int32 i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		bool IsGround;									//나중에 Player와 연결
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
		if (map->TrapList[i].Active)
		{
			Renderer_DrawImage(&map->TrapList[i].Platform.Image, &map->TrapList[i].Platform.Position.X, &map->TrapList[i].Platform.Position.Y);
		}
		else if (!map->TrapList[i].Active)
		{
			Renderer_DrawImage(&map->TrapList[i].Image2, &map->TrapList[i].Platform.Position.X, &map->TrapList[i].Platform.Position.Y);
		}
	}

	for (int i = 0; i < MAX_SAVE_POINT_COUNT; i++)
	{
		Renderer_DrawImage(&map->SavePointList[i].Platform.Image, &map->SavePointList[i].Platform.Position.X, &map->SavePointList[i].Platform.Position.Y);
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
		Image_FreeImage(&map->TrapList[i].Platform.Image);
		Audio_FreeSoundEffect(&map->TrapList[i].effectSound);
	}

	for (int i = 0; i < MAX_SAVE_POINT_COUNT; i++)
	{
		Image_FreeImage(&map->SavePointList[i].Platform.Image);
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

void Platform_CreateRect(Platform* platform)
{
	platform->Rect.left = platform->Position.X;
	platform->Rect.top = platform->Position.Y;
	platform->Rect.right = platform->Position.X + platform->Width;
	platform->Rect.bottom = platform->Position.Y + platform->Height;
}

void Platform_PlatformHorizontalMove(Map* map, Platform* platform)
{
	if (map->ActiveTime >= PLATFORM_MOVE_CYCLE)
	{
		if (!platform->DirectionForCycle)
		{
			platform->Position.X += PLATFORM_MOVE_SPEED;
		}
		else if (platform->DirectionForCycle)
		{
			platform->Position.X -= PLATFORM_MOVE_SPEED;
		}
		map->ActiveTime = 0.0f;
		platform->DirectionForCycle = !platform->DirectionForCycle;
	}
}

void Platform_PlatformVerticalMove(Map* map, Platform* platform)
{
	if (map->ActiveTime >= PLATFORM_MOVE_CYCLE)
	{
		if (!platform->DirectionForCycle)
		{
			platform->Position.Y += PLATFORM_MOVE_SPEED;
		}
		else if (platform->DirectionForCycle)
		{
			platform->Position.Y -= PLATFORM_MOVE_SPEED;
		}
		map->ActiveTime = 0.0f;
		platform->DirectionForCycle = !platform->DirectionForCycle;
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
