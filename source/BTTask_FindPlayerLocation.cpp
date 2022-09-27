// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "MyProject2.h"

#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem.h"
#include "MyAIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "blackboard_keys.h"
#include "MyBot.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation()
{
	NodeName = TEXT("Find Player Location"); // �����̺��Ʈ�������� ��� �̸��� ����
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); // �÷��̾� ĳ����

	if (player)
	{
		auto const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner());
		FVector const player_location = player->GetActorLocation(); // �÷��̾� ĳ���� ��ġ

		if (search_random)
		{
			FNavLocation loc;

			UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

			if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
			{
				cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, player_location);
			}
		}
		else
		{
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, player_location); // �÷��̾� ��ġ�� Ÿ�� ��ġ�� ����
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}