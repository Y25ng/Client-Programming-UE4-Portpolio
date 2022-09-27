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
	AMyBot* const npcBot = Cast<AMyBot>(cont->GetPawn()); // AI�� ������ �޴� ��

	AMyBoss* Boss = Cast<AMyBoss>(npcBot);
	if (Boss != nullptr && Boss->GetbPossibleSkill() == true) // ������� && �ñر� ����� �����ϴٸ�
	{
		if (montage_has_finished(npcBot)) // ���� �ִϸ��̼��� ���������� �ʴٸ�
		{
			Boss->Skill(); // �ñر� ����
		}
	}

	if (ICombatInterface* const icombat = Cast<ICombatInterface>(npcBot)) // �������̽������� �����Լ��� �� Ŭ�������� ������ �ߴٸ� if�� ����
	{
		if ((montage_has_finished(npcBot)) && ((cont->get_blackboard()->GetValueAsBool(bb_keys::player_is_in_AttackRange)) == true))
			// �ִϸ��̼��� ���������� �ʰ� �����ִٸ� & Ÿ���� �������� �ִٸ�
		{
			// UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, npcBot->GetActorLocation());
			icombat->Execute_melee_attack(npcBot); // �����Լ� ����
		}
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_Attack::montage_has_finished(AMyBot* const npcBot) // ���� �ִϸ��̼��� ���������� �ʰ� �����ִ��� ���� ��ȯ
{
	bool result = npcBot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcBot->get_montage());

	AMyBoss* Boss = Cast<AMyBoss>(npcBot);
	if (Boss != nullptr)
	{
		result = (result && (Boss->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Boss->Skill_Anim)));
	}
		
	return result;
}