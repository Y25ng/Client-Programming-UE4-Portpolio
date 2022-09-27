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
	NodeName = TEXT("Find Random Location"); // �����̺��Ʈ�������� ��� �̸��� ����
}

EBTNodeResult::Type UBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory)
{
	auto const cont = Cast<AMyAIController>(owner_Comp.GetAIOwner()); // AI Controller
	auto const npc = cont->GetPawn(); // AI Controller�� ������ �޴� Pawn

	FVector const origin = npc->GetActorLocation(); // npc Pawn�� ��ġ��
	FNavLocation loc;

	auto tempNPC = Cast<ABasicCharacter>(npc);
	AMyBoss* tempBoss = Cast<AMyBoss>(npc);
	if ((tempNPC != nullptr && tempNPC->GetbIsStarting() == true) || (tempBoss != nullptr && tempBoss->GetbDuringSkill() == true))
	{ // ���� �ִϸ��̼����̰ų� ��ų�� �������� �� �̵��� ��ġ�� ���ڸ��� �Ҵ�
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, origin); // �̵��� ��ġ ����
	}
	else
	{
		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
		{
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location); // �̵��� ��ġ ����
		}
	}

	FinishLatentTask(owner_Comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
