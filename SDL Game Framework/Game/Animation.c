#include "stdafx.h"
#include "Animation.h"
#include "Player.h"


void Animation_Init(Animation* animation)
{
	//�⺻ ���� �ʱ�ȭ
	animation->picCount = 0;
	animation->animSpeed = 0.0f;

	//���� ���� �ʱ�ȭ
	prevState = -1;

	//�̹��� �޾ƿ���
	Image_LoadImage(&animation->playerIdleImages[0][0], "Idle_L0.png");
	Image_LoadImage(&animation->playerIdleImages[0][1], "Idle_L1.png");
	Image_LoadImage(&animation->playerIdleImages[1][0], "Idle_R0.png");
	Image_LoadImage(&animation->playerIdleImages[1][1], "Idle_R1.png");

	Image_LoadImage(&animation->playerMoveImages[0][0], "Move_L0.png");
	Image_LoadImage(&animation->playerMoveImages[0][1], "Move_L1.png");
	Image_LoadImage(&animation->playerMoveImages[0][2], "Move_L2.png");
	Image_LoadImage(&animation->playerMoveImages[0][3], "Move_L3.png");
	Image_LoadImage(&animation->playerMoveImages[0][4], "Move_L4.png");
	Image_LoadImage(&animation->playerMoveImages[0][5], "Move_L5.png");
	Image_LoadImage(&animation->playerMoveImages[0][6], "Move_L6.png");
	Image_LoadImage(&animation->playerMoveImages[0][7], "Move_L7.png");

	Image_LoadImage(&animation->playerMoveImages[1][0], "Move_R0.png");
	Image_LoadImage(&animation->playerMoveImages[1][1], "Move_R1.png");
	Image_LoadImage(&animation->playerMoveImages[1][2], "Move_R2.png");
	Image_LoadImage(&animation->playerMoveImages[1][3], "Move_R3.png");
	Image_LoadImage(&animation->playerMoveImages[1][4], "Move_R4.png");
	Image_LoadImage(&animation->playerMoveImages[1][5], "Move_R5.png");
	Image_LoadImage(&animation->playerMoveImages[1][6], "Move_R6.png");
	Image_LoadImage(&animation->playerMoveImages[1][7], "Move_R7.png");

	Image_LoadImage(&animation->playerDEATHImages[0], "Die0.png");
	Image_LoadImage(&animation->playerDEATHImages[1], "Die1.png");
	Image_LoadImage(&animation->playerDEATHImages[2], "Die2.png");
	Image_LoadImage(&animation->playerDEATHImages[3], "Die3.png");
	Image_LoadImage(&animation->playerDEATHImages[4], "Die4.png");
	Image_LoadImage(&animation->playerDEATHImages[5], "Die5.png");
	Image_LoadImage(&animation->playerDEATHImages[6], "Die6.png");
	Image_LoadImage(&animation->playerDEATHImages[7], "Die7.png");
	Image_LoadImage(&animation->playerDEATHImages[8], "Die8.png");
}

void Aniamtion_Update(Player* player)
{
	Animation* animation = Player_GetAnimation(player);

	// ���°� ����� ���� �⺻ ������ �����Ŵ.
	if (prevState != Player_GetState(player))
	{
		prevState = Player_GetState(player);

		switch (Player_GetState(player))
		{
		case PLAYER_IDLE:
		case PLAYER_MOVE:
			animation->animSpeed = 0.5f;
			animation->elapsedTime = 0.0f;
			animation->isLoop = true;
			animation->picCount = 0;
			break;
		case PLAYER_DIE:
			animation->animSpeed = 0.3f;
			animation->elapsedTime = 0.0f;
			animation->isLoop = false;
			animation->picCount = 0;
			break;
		default:
			printf("ERROR!!! WORNG PLAYER STATE!(FRONT)\n");
			return NULL;
			break;
		}
	}

	//�̹��� ������ �ð� �����Ͽ� �̹��� ��ȯ
	if (animation->elapsedTime < animation->animSpeed)
	{
		animation->elapsedTime += Timer_GetDeltaTime();
	}
	else
	{
		animation->picCount++;
		animation->elapsedTime = 0;
		if (animation->picCount > Player_GetState(player))
		{
			if (!animation->isLoop)
			{
				Player_SetState(player, PLAYER_IDLE);
			}
			animation->picCount = 0;
		}
	}

	//���� ���¿� ���� ������ �̹��� ����
	switch (Player_GetState(player))
	{
	case PLAYER_IDLE:
		animation->showImage = &animation->playerIdleImages[player->direction][animation->picCount];
		break;
	case PLAYER_MOVE:
		animation->showImage = &animation->playerIdleImages[player->direction][animation->picCount];
		break;
	case PLAYER_DIE:
		animation->showImage = &animation->playerIdleImages[player->direction][animation->picCount];
		break;
	default:
		printf("ERROR!!! WORNG PLAYER STATE!(BACK)\n");
		break;
	}
}

void Animation_Render(Animation* animation, Position* position)
{
	//�̹��� Render
	if (prevState != PLAYER_DIE)//�÷��̾ �׾��ٸ� �ش� �̹��� ũ�⿡ ���� �ٽ� ��ġ ����
	{
		Renderer_DrawImage(animation->showImage, position->X, position->Y);
	}
	else 
	{
		Renderer_DrawImage(animation->showImage, position->X, position->Y - (animation->showImage->Height - animation->playerIdleImages[0][0].Height));
	}
}

void Animation_Release(Animation* animation)
{
	//�̹��� Free
	Image_FreeImage(&animation->playerIdleImages[0][0]);
	Image_FreeImage(&animation->playerIdleImages[0][1]);
	Image_FreeImage(&animation->playerIdleImages[1][0]);
	Image_FreeImage(&animation->playerIdleImages[1][1]);

	Image_FreeImage(&animation->playerMoveImages[0][0]);
	Image_FreeImage(&animation->playerMoveImages[0][1]);
	Image_FreeImage(&animation->playerMoveImages[0][2]);
	Image_FreeImage(&animation->playerMoveImages[0][3]);
	Image_FreeImage(&animation->playerMoveImages[0][4]);
	Image_FreeImage(&animation->playerMoveImages[0][5]);
	Image_FreeImage(&animation->playerMoveImages[0][6]);
	Image_FreeImage(&animation->playerMoveImages[0][7]);

	Image_FreeImage(&animation->playerMoveImages[1][0]);
	Image_FreeImage(&animation->playerMoveImages[1][1]);
	Image_FreeImage(&animation->playerMoveImages[1][2]);
	Image_FreeImage(&animation->playerMoveImages[1][3]);
	Image_FreeImage(&animation->playerMoveImages[1][4]);
	Image_FreeImage(&animation->playerMoveImages[1][5]);
	Image_FreeImage(&animation->playerMoveImages[1][6]);
	Image_FreeImage(&animation->playerMoveImages[1][7]);

	Image_FreeImage(&animation->playerDEATHImages[0]);
	Image_FreeImage(&animation->playerDEATHImages[1]);
	Image_FreeImage(&animation->playerDEATHImages[2]);
	Image_FreeImage(&animation->playerDEATHImages[3]);
	Image_FreeImage(&animation->playerDEATHImages[4]);
	Image_FreeImage(&animation->playerDEATHImages[5]);
	Image_FreeImage(&animation->playerDEATHImages[6]);
	Image_FreeImage(&animation->playerDEATHImages[7]);
	Image_FreeImage(&animation->playerDEATHImages[8]);
}