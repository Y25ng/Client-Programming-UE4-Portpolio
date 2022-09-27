// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInAttackRange.h"

#include "MyBot.h"
#include "MyAIController.h"
#include "MyBasicCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UBTService_IsPlayerInAttackRange::UBTService_IsPlayerInAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Attack Range");
}

void UBTService_IsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner());
	AMyBot* const npcBot = Cast<AMyBot>(cont->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (player == nullptr) // 플레이어가 없다면 블랙보드에서 can_see_player에 false 할당
	{
		cont->get_blackboard()->SetValueAsBool(bb_keys::can_see_player, false);
		return;
	}

	/*
	플레이어와의 거리가 Attack_range 이하라면 블랙보드에서 player_is_in_AttackRange에 true 할당
	플레이어와의 거리가 Attack_range 이상이라면 블랙보드에서 player_is_in_AttackRange에 false 할당	
	*/

	float distance = npcBot->GetDistanceTo(player);

	if(distance <= Attack_range)
		cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_AttackRange, true);
	else
		cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_AttackRange, false);
}