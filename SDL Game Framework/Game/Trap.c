#include "Trap.h"

void Trap_TrapMove(Trap* trap, Player* player)
{
	if (!(trap->Type == TRAP_FLYING) && !(trap->Type == TRAP_TRACK))	// 함정 종류 : 날아오는, 따라오는
	{
		return;
	}
	if (!trap->Active) // 발동 조건
	{
		return;
	}
	if (trap->ActiveTime < TRAP_SWITCH_CYCLE)
	{
		return;
	}
	Trap_GetTrackTargetPosition(trap, player);

	int32 trapX = trap->Platform.Position.X;
	int32 trapY = trap->Platform.Position.Y;
	int32 targetX = trap->TargetPosition.X;
	int32 targetY = trap->TargetPosition.Y;

	if (trapX > targetX)
	{
		if (trapX - trap->Speed > targetX)
		{
			trap->Platform.Position.X -= trap->Speed;
		}
		else
		{
			trap->Platform.Position.X = targetX;
		}
	}
	else if (trapX < targetX)
	{
		if (trapX + trap->Speed < targetX)
		{
			trap->Platform.Position.X += trap->Speed;
		}
		else
		{
			trap->Platform.Position.X = targetX;
		}
	}

	if (trapY > targetY)
	{
		if (trapY - trap->Speed > targetY)
		{
			trap->Platform.Position.Y -= trap->Speed;
		}
		else
		{
			trap->Platform.Position.Y = targetY;
		}
	}
	else if (trapY < targetY)
	{
		if (trapY + trap->Speed < targetY)
		{
			trap->Platform.Position.Y += trap->Speed;
		}
		else
		{
			trap->Platform.Position.Y = targetY;
		}
	}
	trap->ActiveTime = 0.0f;

}

void Trap_InitializeTargetPosition(Trap* trap, int32 x, int32 y)
{
	if (trap->Type == TRAP_FLYING)
	{
		trap->TargetPosition.X = x;
		trap->TargetPosition.Y = y;
	}
	else
	{
		trap->TargetPosition.X = trap->Platform.Position.X;
		trap->TargetPosition.Y = trap->Platform.Position.Y;
	}
}

void Trap_GetTrackTargetPosition(Trap* trap, Player* player)
{
	if (trap->Type == TRAP_TRACK)
	{
		trap->TargetPosition.X = player->position.X;
		trap->TargetPosition.Y = player->position.Y;
	}

	/*return trap->TargetPosition;*/
}

void Trap_TrapSwitch(Trap* trap)
{
	trap->ActiveTime += Timer_GetDeltaTime(); // 변경할지도 모른다.
	if (trap->Type == TRAP_SWITCH)
	{
		return;
	}

	if (trap->ActiveTime >= TRAP_SWITCH_CYCLE)
	{
		trap->Active = !trap->Active;

		trap->ActiveTime = 0.0f;
	}
}