// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBombAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBot.h"

void UMyBombAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringAttack(true); // AnimMontage의 Begin 지점부터 공격중이라고 판단

			AMyBot* Bot = Cast<AMyBot>(Player);
			if (Bot)
			{
				Bot->ThrowBomb(); // 폭탄을 던짐
			}
		}
	}
}

void UMyBombAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->AttackEnd(); // AnimMontage의 End 지점에서 공격 종료 함수 실행
		}
	}
}