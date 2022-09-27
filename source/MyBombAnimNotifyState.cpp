// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBombAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBot.h"

void UMyBombAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringAttack(true); // AnimMontage�� Begin �������� �������̶�� �Ǵ�

			AMyBot* Bot = Cast<AMyBot>(Player);
			if (Bot)
			{
				Bot->ThrowBomb(); // ��ź�� ����
			}
		}
	}
}

void UMyBombAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->AttackEnd(); // AnimMontage�� End �������� ���� ���� �Լ� ����
		}
	}
}