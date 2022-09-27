// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomMove.h"
#include "MyProject2.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "MyAIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "blackboard_keys.h"
#include "BasicCharacter.h"
#include "MyBoss.h"

UBTTask_RandomMove::UBTTask_RandomMove(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location"); // 비헤이비어트리에서의 노드 이름을 지정
}

EBTNodeResult::Type UBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory)
{
	auto const cont = Cast<AMyAIController>(owner_Comp.GetAIOwner()); // AI Controller
	auto const npc = cont->GetPawn(); // AI Controller의 조종을 받는 Pawn

	FVector const origin = npc->GetActorLocation(); // npc Pawn의 위치값
	FNavLocation loc;

	auto tempNPC = Cast<ABasicCharacter>(npc);
	AMyBoss* tempBoss = Cast<AMyBoss>(npc);
	if ((tempNPC != nullptr && tempNPC->GetbIsStarting() == true) || (tempBoss != nullptr && tempBoss->GetbDuringSkill() == true))
	{ // 시작 애니메이션중이거나 스킬이 진행중일 땐 이동할 위치를 제자리로 할당
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, origin); // 이동할 위치 지정
	}
	else
	{
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
		{
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location); // 이동할 위치 지정
		}
	}

	FinishLatentTask(owner_Comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
