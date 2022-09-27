// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MyAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "BasicCharacter.h"
#include "MyBot.h"
#include "MyBoss.h"
#include "blackboard_keys.h"
#include "CombatInterface.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_Attack::UBTTask_Attack(FObjectInitializer const& object_intializer)
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AMyAIController* const cont = Cast<AMyAIController>(owner_comp.GetAIOwner());
	AMyBot* const npcBot = Cast<AMyBot>(cont->GetPawn()); // AI의 조종을 받는 봇

	AMyBoss* Boss = Cast<AMyBoss>(npcBot);
	if (Boss != nullptr && Boss->GetbPossibleSkill() == true) // 보스라면 && 궁극기 사용이 가능하다면
	{
		if (montage_has_finished(npcBot)) // 공격 애니메이션이 진행중이지 않다면
		{
			Boss->Skill(); // 궁극기 실행
		}
	}

	if (ICombatInterface* const icombat = Cast<ICombatInterface>(npcBot)) // 인터페이스에서의 가상함수를 봇 클래스에서 재정의 했다면 if문 실행
	{
		if ((montage_has_finished(npcBot)) && ((cont->get_blackboard()->GetValueAsBool(bb_keys::player_is_in_AttackRange)) == true))
			// 애니메이션이 진행중이지 않고 멈춰있다면 & 타겟이 범위내에 있다면
		{
			// UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, npcBot->GetActorLocation());
			icombat->Execute_melee_attack(npcBot); // 공격함수 실행
		}
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_Attack::montage_has_finished(AMyBot* const npcBot) // 공격 애니메이션이 진행중이지 않고 멈춰있는지 여부 반환
{
	bool result = npcBot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcBot->get_montage());

	AMyBoss* Boss = Cast<AMyBoss>(npcBot);
	if (Boss != nullptr)
	{
		result = (result && (Boss->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Boss->Skill_Anim)));
	}
		
	return result;
}