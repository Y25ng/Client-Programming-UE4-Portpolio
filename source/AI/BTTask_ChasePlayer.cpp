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
	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner()); // 컨트롤러
	auto npc = cont->GetPawn(); // 컨트롤러가 조종하는 봇 할당
	FVector const player_location = cont->get_blackboard()->GetValueAsVector(bb_keys::target_location); // 타겟 위치를 블랙보드에서 가져옴

	auto tempNPC = Cast<ABasicCharacter>(npc);
	AMyBoss* tempBoss = Cast<AMyBoss>(npc);
	if ((tempNPC != nullptr && tempNPC->GetbIsStarting() == true) || (tempBoss != nullptr && tempBoss->GetbDuringSkill() == true))
	{
		; // 몬스터의 start 모션이 진행중이거나 보스의 스킬이 진행중인 경우에는 Chase를 수행하지 않음
	}
	else if ((cont->get_blackboard()->GetValueAsBool(bb_keys::player_is_in_AttackRange)) == true) // 블랙보드에서 정보를 가져옴 -> 타겟이 공격 범위 내에 있는지
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, npc->GetActorLocation());
		/*
		
		타겟이 공격 범위 내에 있을 시 타겟이 움직여도 타겟의 방향으로 회전만 진행

		*/

		FVector ToTarget = player_location - npc->GetActorLocation();
		ToTarget.Z = 0.0f;

		// FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
		// npc->SetActorRotation(LookAtRotation);

		FRotator TargetRot = FRotationMatrix::MakeFromX(ToTarget).Rotator();
		npc->SetActorRotation(FMath::RInterpTo(npc->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 40.f));
	}
	else // 타겟이 공격 범위 내에 없을 시
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, player_location); // 타겟의 위치로 이동
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	//return EBTNodeResult::Type();
	return EBTNodeResult::Type();
}

