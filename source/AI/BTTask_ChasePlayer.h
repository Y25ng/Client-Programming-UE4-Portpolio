// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Mybot.h"
#include "MyBoss.h"
#include "BTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UBTTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_ChasePlayer();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_momory) override;

};
