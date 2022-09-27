// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBotAnimNotifyState.h"
#include "MyBoss.h"

void UMyBotAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringAttack(true); // AnimMontage의 Begin 지점부터 공격중이라고 판단
			Player->SetbDamagePossible(true); // 이 시점부터 데미지 가능
		}
	}
}

void UMyBotAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbDamagePossible(false); // 이 시점부터 데미지 불가능
			Player->AttackEnd(); // AnimMontage의 End 지점에서 공격 종료 함수 실행

			AMyBoss* MyBoss = Cast<AMyBoss>(Player);
			if(MyBoss != nullptr)
				MyBoss->PlaySound("AttackBottomCollision"); // 보스의 경우 바닥을 치는 효과음 재생
		}
	}
}