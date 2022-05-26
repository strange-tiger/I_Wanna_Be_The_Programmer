#include "Trap.h"

void Trap_TrapMove(Trap* trap, Player* player, int32 x, int32 y)
{
	if (trap->Type == TRAP_FLYING || trap->Type == TRAP_TRACK)	// 함정 종류 : 날아오는, 따라오는
	{
		Trap_GetTargetPosition(trap, player, x, y);

		if (trap->Active) // 발동 조건
		{
			int32 trapX = trap->Position.X;
			int32 trapY = trap->Position.Y;
			int32 targetX = trap->TargetPosition.X;
			int32 targetY = trap->TargetPosition.Y;

			if (trap->ActiveTime >= TRAP_SWITCH_CYCLE)
			{
				if (trapX > targetX)
				{
					if (trapX - trap->Speed > targetX)
					{
						trap->Position.X -= trap->Speed;
					}
					else
					{
						trap->Position.X = targetX;
					}
				}
				else if (trapX < targetX)
				{
					if (trapX + trap->Speed < targetX)
					{
						trap->Position.X += trap->Speed;
					}
					else
					{
						trap->Position.X = targetX;
					}
				}

				if (trapY > targetY)
				{
					if (trapY - trap->Speed > targetY)
					{
						trap->Position.Y -= trap->Speed;
					}
					else
					{
						trap->Position.Y = targetY;
					}
				}
				else if (trapY < targetY)
				{
					if (trapY + trap->Speed < targetY)
					{
						trap->Position.Y += trap->Speed;
					}
					else
					{
						trap->Position.Y = targetY;
					}
				}
				trap->ActiveTime = 0.0f;
			}
		}
	}
}

void Trap_GetTargetPosition(Trap* trap, Player* player, int32 x, int32 y)
{
	if (trap->Type == TRAP_TRACK)
	{
		trap->TargetPosition = player->Position;
	}
	else if (trap->Type == TRAP_BASIC || trap->Type == TRAP_SWITCH)
	{
		trap->TargetPosition = trap->Position;
	}
	else if (trap->Type == TRAP_FLYING)
	{
		trap->TargetPosition.X = x;
		trap->TargetPosition.Y = y;
	}
}

void Trap_TrapSwitch(Trap* trap)
{
	if (trap->Type == TRAP_SWITCH)
	{
		trap->ActiveTime += Timer_GetDeltaTime(); // 변경할지도 모른다.

		if (trap->ActiveTime >= TRAP_SWITCH_CYCLE)
		{
			trap->Active = !trap->Active;
			
			trap->ActiveTime = 0.0f;
		}
	}
	
}
