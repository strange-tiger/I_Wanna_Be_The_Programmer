#include "Type.h"
#include "stdafx.h"
#include "Framework.h"
#include "Player.h"

#define PLAYER_X_SPEED			15
#define PLAYER_Y_SPEED			-30
#define PLAYER_DIRECTION_RIGHT	0
#define PLAYER_DIRECTION_LEFT	1
#define PLAYER_JUMP_TIME_LENGTH	0.1f

void PlayerMove(int32* playerX, int32* playerY, int32* playerDirection, RECT* playerRect, RECT* platformRect, int32* Jump, float* JumpTime, bool IsGround)
{
	RECT tempRect;

	if (Input_GetKeyDown(VK_SPACE))
	{
		*Jump += 1;
	}
	if (Input_GetKey(VK_LEFT))
	{
		if (!IntersectRect(&tempRect, playerRect, platformRect))
		{
			*playerX -= PLAYER_X_SPEED;
		}
		*playerDirection = PLAYER_DIRECTION_RIGHT;
	}

	if (Input_GetKey(VK_RIGHT))
	{
		if (!IntersectRect(&tempRect, playerRect, platformRect))
		{
			*playerX += PLAYER_X_SPEED;
		}
		*playerDirection = PLAYER_DIRECTION_LEFT;
	}

	if (*Jump >= 1)
	{
		*JumpTime += Timer_GetDeltaTime();
		if (*JumpTime <= PLAYER_JUMP_TIME_LENGTH)
		{
			*playerY += PLAYER_Y_SPEED;
		}
		if (*JumpTime > PLAYER_JUMP_TIME_LENGTH)
		{
			*JumpTime = 0.0f;
			*Jump = 0;
		}
	}

	if (*Jump == 0)
	{
		if (!IsGround)
		{
			*playerY -= PLAYER_Y_SPEED;
		}
	}
	
	if (Input_GetKey(VK_UP))
	{

	}

	if (Input_GetKey(VK_DOWN))
	{

	}
}