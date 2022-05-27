#include "Map.h"
#include "Trap.h"

void Map_Init(Map* map, int32 StageNum)
{
	// �׽�Ʈ��
	//CsvFile* csvFile;
	//CreateCsvFile(csvFile, "CsvTest.csv");

	Image_LoadImage(&map->BackGroundImage, "");			// ��� �̹��� �ε�
	Audio_LoadMusic(&map->BGM, "");						// ��� ���� �ε�
	Audio_LoadMusic(&map->DieBGM, "");					// ����� ���� �ε�

	Image_LoadImage(&map->Radder.Platform.Image, "");	// Radder �̹��� �ε�
	map->Radder.Active = false;							// Radder Ȱ�� �ʱ�ȭ
	map->Radder.Event = NULL;							// Radder �̺�Ʈ �ʱ�ȭ

	//�� ���� ���� ��ǥ �ʱ�ȭ										/// csv�Ľ� �ʿ�
	map->StartPoint.X = 0;
	map->StartPoint.Y = 0;

	//�� ���� ���� ��ǥ �ʱ�ȭ										/// csv�Ľ� �ʿ�
	map->DestinationPoint.X = 0;
	map->DestinationPoint.Y = 0;

	//��ŸŸ�� ���� �ʱ�ȭ
	map->ActiveTime = 0.0f;

	for (int i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		// Platform �̹��� �ε�
		Image_LoadImage(&map->PlatformList[i].Image, "");			/// csv�Ľ� �ʿ�

		// ��ǥ �� ���μ��� �� �ʱ�ȭ									/// csv�Ľ� �ʿ�
		map->PlatformList[i].Position.X = 0;
		map->PlatformList[i].Position.Y = 0;
		map->PlatformList[i].Width = 0;
		map->PlatformList[i].Height = 0;
				
		// Platform Rect ����
		Platform_CreateRect(&map->PlatformList[i]);
	}

	for (int i = 0; i < MAX_TRAP_COUNT; i++)
	{
		// Trap �̹��� �ε�
		Image_LoadImage(&map->TrapList[i].Platform.Image, "");		/// csv�Ľ� �ʿ�
		// Trap �ٲ� �̹��� �ε� 
		Image_LoadImage(&map->TrapList[i].Image2, "");				/// csv�Ľ� �ʿ�
		// Trap ����� �ε�
		Audio_LoadSoundEffect(&map->TrapList[i].effectSound, "");	/// csv�Ľ� �ʿ�
		
		// ��ǥ �� ���μ��� �� �ʱ�ȭ									/// csv�Ľ� �ʿ�
		map->TrapList[i].Platform.Position.X = 0;
		map->TrapList[i].Platform.Position.Y = 0;
		map->TrapList[i].Platform.Width = 0;
		map->TrapList[i].Platform.Height = 0;

		// Trap Rect ����
		Platform_CreateRect(&map->TrapList[i].Platform);

		map->TrapList[i].Type = TRAP_BASIC;	// Trap Ÿ�� �ʱ�ȭ		/// csv�Ľ� �ʿ�

		map->TrapList[i].Active = true;		// Trap Ȱ��ȭ �ʱ�ȭ	/// csv�Ľ� �ʿ�
		map->TrapList[i].ActiveTime = 0.0f;	// Trap ��ŸŸ�� �ʱ�ȭ	/// csv�Ľ� �ʿ�

		map->TrapList[i].TargetPosition.X = 0;	// Trap Ÿ�� ��ġ X �ʱ�ȭ // ���� or �÷��̾� ��ġ
		map->TrapList[i].TargetPosition.Y = 0;	// Trap Ÿ�� ��ġ Y �ʱ�ȭ // ���� or �÷��̾� ��ġ

		map->TrapList[i].ImageAlpha = 255;	// ImageAlpha �ʱ�ȭ		/// ���� �� csv�Ľ� ���� Ȯ�� ��
	}

	for (int i = 0; i < MAX_SAVE_POINT_COUNT; i++)
	{
		// SavePoint �̹��� �ε�
		Image_LoadImage(&map->SavePointList[i].Platform.Image, "");	/// csv�Ľ� �ʿ�

		// ��ǥ �� ���μ��� �� �ʱ�ȭ									/// csv�Ľ� �ʿ�
		map->SavePointList[i].Platform.Position.X = 0;
		map->SavePointList[i].Platform.Position.Y = 0;
		map->SavePointList[i].Platform.Width = 0;
		map->SavePointList[i].Platform.Height = 0;

		// Platform Rect ����
		Platform_CreateRect(&map->SavePointList[i].Platform);

		map->SavePointList[i].Active = false;			//SavePoint Ȱ���� �ʱ�ȭ
	}

	for (int i = 0; i < MAX_SWITCH_COUNT; i++)
	{
		//Image_LoadImage(&map->SwitchList[i].Platform.Image, "");			// Switch �̹��� �ε� // csv �Ľ� �� // �ʿ���� �Ŷ� ����

		// ��ǥ �� ���μ��� �� �ʱ�ȭ									/// csv�Ľ� �ʿ�
		map->SwitchList[i].Platform.Position.X = 0;
		map->SwitchList[i].Platform.Position.Y = 0;
		map->SwitchList[i].Platform.Width = 0;
		map->SwitchList[i].Platform.Height = 0;

		// Platform Rect ����
		Platform_CreateRect(&map->SwitchList[i].Platform);

		map->SwitchList[i].Active = false;				//SavePoint Ȱ���� �ʱ�ȭ

		map->SwitchList[i].Event = NULL;
	}
}

void Map_Update(Map* map, Player* player)	// player ������ ���� ���� �³�..?
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
		Trap_TrapMove(&map->TrapList[i], player, x, y);				/// csv�Ľ� �ʿ�
		Trap_TrapSwitch(&map->TrapList[i]);
	}

	if (map->ActiveTime > PLATFORM_MOVE_CYCLE)
	{
		map->ActiveTime = 0.0f;
	}

	Map_DetectSavePoint(map, player);

	for (int32 i = 0; i < MAX_PLATFORM_COUNT; i++)
	{
		bool IsGround;									//���߿� Player�� ����
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
			if (IntersectRect(&tempRect, &player->Rect, &map->SavePointList[i].Platform.Rect)) // �÷��̾�� ���̺� ����Ʈ �浹 ó��
			{
				map->SavePointList[i].Active = !map->SavePointList[i].Active;

				map->RespawnPoint = map->SavePointList[i].Platform.Position;
			}
		}
	}
}
