// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBotAnimNotifyState.h"
#include "MyBoss.h"

void UMyBotAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringAttack(true); // AnimMontage�� Begin �������� �������̶�� �Ǵ�
			Player->SetbDamagePossible(true); // �� �������� ������ ����
		}
	}
}

void UMyBotAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbDamagePossible(false); // �� �������� ������ �Ұ���
			Player->AttackEnd(); // AnimMontage�� End �������� ���� ���� �Լ� ����

			AMyBoss* MyBoss = Cast<AMyBoss>(Player);
			if(MyBoss != nullptr)
				MyBoss->PlaySound("AttackBottomCollision"); // ������ ��� �ٴ��� ġ�� ȿ���� ���
		}
	}
}