// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBasicCharacter.h"


void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringAttack(true); // AnimMontage의 Begin 지점부터 공격중이라고 판단
			Player->SetbDamagePossible(true); // 이 시점부터 데미지 가능

			AMyBasicCharacter* MyPlayer = Cast<AMyBasicCharacter>(Player);

			if (MyPlayer)
			{
				MyPlayer->PlaySound("BasicAttack");
			}
		}
	}
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->AttackEnd(); // AnimMontage의 End 지점에서 공격 종료 함수 실행 // Player->SetbIsDuringAttack(false); 와 같음
			Player->SetbDamagePossible(false); // 이 시점부터 데미지 불가능
			Player->SetbJumpAttack(false);
		}
	}
}