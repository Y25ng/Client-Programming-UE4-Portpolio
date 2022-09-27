// Fill out your copyright notice in the Description page of Project Settings.


#include "MyJumpEndAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBasicCharacter.h"

void UMyJumpEndAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringJumpEnd(true); // AnimMontage의 Begin 지점부터 점프 End가 시작되었다고 판단

			AMyBasicCharacter* TempPlayer = Cast<AMyBasicCharacter>(Player);
			if (TempPlayer)
				TempPlayer->PlaySound("JumpEnd"); // 바닥 착지 소리 출력
		}
	}
}

void UMyJumpEndAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringJumpEnd(false); // AnimMontage의 End 지점부터 점프 End가 종료되었다고 판단
		}
	}
}