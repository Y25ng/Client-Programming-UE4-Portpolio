// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"
#include "MyBot.h"
#include "MyBasicCharacter.h"
#include "MyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);
	auto const cont = owner_comp.GetAIOwner();
	AMyBot* const npcBot = Cast<AMyBot>(cont->GetPawn());

	if (npcBot)
	{
		npcBot->GetCharacterMovement()->MaxWalkSpeed = speed; // speed 값을 MaxWalkSpeed에 할당
	}
}

FString UBTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the NpcBot speed");
}