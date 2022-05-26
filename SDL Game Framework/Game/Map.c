#include "Map.h"
#include "Trap.h"

void Map_Init(Map* map, int32 StageNum)
{
	// �׽�Ʈ��
	//CsvFile* csvFile;
	//CreateCsvFile(csvFile, "CsvTest.csv");

	Image_LoadImage(&map->BackGroundImage, "");
	Audio_LoadMusic(&map->BGM, "");
	Audio_LoadMusic(&map->DieBGM, "");

	map->StartPoint.X = 0;
	map->StartPoint.Y = 0;

	map->DestinationPoint.X = 0;
	map->DestinationPoint.Y = 0;

	map->ActiveTime = 0.0f;

	for (int i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		Image_LoadImage(&map->PlatformList[i].Image, "");			// Platform �̹��� �ε� // csv �Ľ� ��

		// ��ǥ �� ���μ��� �� �ʱ�ȭ // csv �Ľ� ��
		map->PlatformList[i].Position.X = 0;
		int32 platformX = map->PlatformList[i].Position.X;

		map->PlatformList[i].Position.Y = 0;
		int32 platformY = map->PlatformList[i].Position.Y;

		map->PlatformList[i].Width = 0;
		int32 platformWidth = map->PlatformList[i].Width;

		map->PlatformList[i].Height = 0;
		int32 platformHeight = map->PlatformList[i].Height;

		// Platform Rect ����
		map->PlatformList[i].Rect.left		= platformX - platformWidth / 2;
		map->PlatformList[i].Rect.top		= platformY - platformHeight / 2;
		map->PlatformList[i].Rect.right		= platformX + platformWidth / 2;
		map->PlatformList[i].Rect.bottom	= platformY + platformHeight / 2;
	}

	for (int i = 0; i < MAX_TRAP_COUNT; i++)
	{
		Image_LoadImage(&map->TrapList[i].Image, "");				// Trap �̹��� �ε� // csv �Ľ� ��
		
		// ��ǥ �� ���μ��� �� �ʱ�ȭ // csv �Ľ� ��
		map->TrapList[i].Position.X = 0;
		int32 trapX = map->TrapList[i].Position.X;

		map->TrapList[i].Position.Y = 0;
		int32 trapY = map->TrapList[i].Position.Y;

		map->TrapList[i].Width = 0;
		int32 trapWidth = map->TrapList[i].Width;

		map->TrapList[i].Height = 0;
		int32 trapHeight = map->TrapList[i].Height;

		// Trap Rect ����
		map->TrapList[i].Rect.left			= trapX - trapWidth / 2;
		map->TrapList[i].Rect.top			= trapY - trapHeight / 2;
		map->TrapList[i].Rect.right			= trapX + trapWidth / 2;
		map->TrapList[i].Rect.bottom		= trapY + trapHeight / 2;

		map->TrapList[i].Type = TRAP_BASIC;							// Trap Ÿ�� �ʱ�ȭ // csv �Ľ� ��
		map->TrapList[i].TargetPosition.X = 0;							// Trap Ÿ�� ��ġ X �ʱ�ȭ // ���� or �÷��̾� ��ġ
		map->TrapList[i].TargetPosition.Y = 0;							// Trap Ÿ�� ��ġ Y �ʱ�ȭ // ���� or �÷��̾� ��ġ

		map->TrapList[i].ImageAlpha = 255;							// ImageAlpha �ʱ�ȭ // csv �Ľ� ��

		Audio_LoadSoundEffect(&map->TrapList[i].effectSound, "");	// Trap ����� �ε� // csv �Ľ� ��
		Image_LoadImage(&map->TrapList[i].Image2, "");				// Trap ����� �̹��� �ε� // csv �Ľ� ��
	}
}

void Map_Update(Map* map)
{
	map->ActiveTime += Timer_GetDeltaTime();


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

bool Map_DetectIsGround(Map* map, Player* player)
{
	RECT tempRect;
	for (int i; i < MAX_PLATFORM_COUNT; i++)
	{
		if (player->Rect.bottom < map->PlatformList[i].Rect.top)
		{
			break;
		}
		if (IntersectRect(&tempRect, &player->Rect, &map->PlatformList[i].Rect))
		{

		}
	}
}

void Map_PlatformHorizontalMove(Map* map, Platform* platform)
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

void Map_PlatformVerticalMove(Map* map, Platform* platform)
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

int32* Map_DetectSavePoint(Map* map, Player* player)
{
	int p[2];

	for (int i = 0; i < MAX_SAVE_POINT_COUNT; i++)
	{
		if (map->SavePoint[i].Active == false)
		{
			if (1) // �浹 ó��? 
			{
				map->SavePoint[i].Active = !map->SavePoint[i].Active;

				p[0] = map->SavePoint[i].Platform.Position.X;
				p[1] = map->SavePoint[i].Platform.Position.Y;
			}
		}
	}

	return p;
}
