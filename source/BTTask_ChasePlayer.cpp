// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_momory)
{
	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner()); // ��Ʈ�ѷ�
	auto npc = cont->GetPawn(); // ��Ʈ�ѷ��� �����ϴ� �� �Ҵ�
	FVector const player_location = cont->get_blackboard()->GetValueAsVector(bb_keys::target_location); // Ÿ�� ��ġ�� �����忡�� ������

	auto tempNPC = Cast<ABasicCharacter>(npc);
	AMyBoss* tempBoss = Cast<AMyBoss>(npc);
	if ((tempNPC != nullptr && tempNPC->GetbIsStarting() == true) || (tempBoss != nullptr && tempBoss->GetbDuringSkill() == true))
	{
		; // ������ start ����� �������̰ų� ������ ��ų�� �������� ��쿡�� Chase�� �������� ����
	}
	else if ((cont->get_blackboard()->GetValueAsBool(bb_keys::player_is_in_AttackRange)) == true) // �����忡�� ������ ������ -> Ÿ���� ���� ���� ���� �ִ���
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, npc->GetActorLocation());
		/*
		
		Ÿ���� ���� ���� ���� ���� �� Ÿ���� �������� Ÿ���� �������� ȸ���� ����

		*/

		FVector ToTarget = player_location - npc->GetActorLocation();
		ToTarget.Z = 0.0f;

		// FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
		// npc->SetActorRotation(LookAtRotation);

		FRotator TargetRot = FRotationMatrix::MakeFromX(ToTarget).Rotator();
		npc->SetActorRotation(FMath::RInterpTo(npc->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 40.f));
	}
	else // Ÿ���� ���� ���� ���� ���� ��
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, player_location); // Ÿ���� ��ġ�� �̵�
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	//return EBTNodeResult::Type();
	return EBTNodeResult::Type();
}

