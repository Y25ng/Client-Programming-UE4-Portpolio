// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBotHitAnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBot.h"

void UMyBotHitAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringHitAnim(true); // AnimMontage의 Begin 지점부터 Hit Anim이 시작됐음을 알림
		}
	}
}

void UMyBotHitAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		ABasicCharacter* Player = Cast< ABasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->SetbIsDuringHitAnim(false); // AnimMontage의 End 지점부터 Hit Anim이 끝났음을 알림
		}
	}
}
