#include "Map.h"
#include "Trap.h"

void Map_Init(Map* map, int32 StageNum)
{
	// 테스트용
	CsvFile* csvFile;
	CreateCsvFile(csvFile, "CsvTest.csv");

	Image_LoadImage(&map->BackGroundImage, "");
	Audio_LoadMusic(&map->BGM, "");

	for (int i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		Image_LoadImage(&map->PlatformList[i].Image, "");
		map->PlatformList[i].Position.X = 0;
		int32 platformX = map->PlatformList[i].Position.X;

		map->PlatformList[i].Position.Y = 0;
		int32 platformY = map->PlatformList[i].Position.Y;

		map->PlatformList[i].Width = 0;
		int32 platformWidth = map->PlatformList[i].Width;

		map->PlatformList[i].Height = 0;
		int32 platformHeight = map->PlatformList[i].Height;

		map->PlatformList[i].Rect.left		= platformX - platformWidth / 2;
		map->PlatformList[i].Rect.top		= platformY - platformHeight / 2;
		map->PlatformList[i].Rect.right		= platformX + platformWidth / 2;
		map->PlatformList[i].Rect.bottom	= platformY + platformHeight / 2;
	}

	

}

void Map_Update(Map* map)
{

}

void Map_Render(Map* map)
{
	Renderer_DrawImage(&map->BackGroundImage, 0, 0);

}

void Map_Release(Map* map)
{
	Image_FreeImage(&map->BackGroundImage);
	Audio_FreeMusic(&map->BGM);
}
