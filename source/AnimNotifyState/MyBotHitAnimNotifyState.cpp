// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBotHitAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBot.h"

void UMyBotHitAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringHitAnim(true); // AnimMontage�� Begin �������� Hit Anim�� ���۵����� �˸�
		}
	}
}

void UMyBotHitAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringHitAnim(false); // AnimMontage�� End �������� Hit Anim�� �������� �˸�
		}
	}
}
