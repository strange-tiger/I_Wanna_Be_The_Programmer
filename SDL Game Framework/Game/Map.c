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
}

void Map_Update(Map* map)
{

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
