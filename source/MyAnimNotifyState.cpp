// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBasicCharacter.h"


void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringAttack(true); // AnimMontage�� Begin �������� �������̶�� �Ǵ�
			Player->SetbDamagePossible(true); // �� �������� ������ ����

			AMyBasicCharacter* MyPlayer = Cast<AMyBasicCharacter>(Player);

			if (MyPlayer)
			{
				MyPlayer->PlaySound("BasicAttack");
			}
		}
	}
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->AttackEnd(); // AnimMontage�� End �������� ���� ���� �Լ� ���� // Player->SetbIsDuringAttack(false); �� ����
			Player->SetbDamagePossible(false); // �� �������� ������ �Ұ���
			Player->SetbJumpAttack(false);
		}
	}
}