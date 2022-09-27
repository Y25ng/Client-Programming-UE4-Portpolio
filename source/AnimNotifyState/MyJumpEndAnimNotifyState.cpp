// Fill out your copyright notice in the Description page of Project Settings.


#include "MyJumpEndAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBasicCharacter.h"

void UMyJumpEndAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringJumpEnd(true); // AnimMontage�� Begin �������� ���� End�� ���۵Ǿ��ٰ� �Ǵ�

			AMyBasicCharacter* TempPlayer = Cast<AMyBasicCharacter>(Player);
			if (TempPlayer)
				TempPlayer->PlaySound("JumpEnd"); // �ٴ� ���� �Ҹ� ���
		}
	}
}

void UMyJumpEndAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringJumpEnd(false); // AnimMontage�� End �������� ���� End�� ����Ǿ��ٰ� �Ǵ�
		}
	}
}