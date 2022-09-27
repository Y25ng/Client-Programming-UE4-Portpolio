// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBot.h"
#include "MyBasicCharacter.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Attack(FObjectInitializer const& object_intializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;

private:
	bool montage_has_finished(AMyBot* const npcBot); // 애니메이션이 진행중이지 않고 멈춰있는지 여부 반환

};