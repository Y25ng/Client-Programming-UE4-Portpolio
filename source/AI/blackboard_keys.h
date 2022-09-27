#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace bb_keys
{
	TCHAR const* const target_location = TEXT("TargetLocation"); // 적이 공격할 타겟
	TCHAR const* const can_see_player = TEXT("CanSeePlayer"); // 타겟이 적의 시야 안에 들어왔는지에 대한 여부
	TCHAR const* const player_is_in_AttackRange = TEXT("playerisinAttackRange"); // 타겟이 적의 공격범위 안에 들어왔는지에 대한 여부
}