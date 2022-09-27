// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFootStepAnimNotifyState.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"

void UMyFootStepAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(MeshComp->GetOwner());
		AMyBot* Bot = Cast<AMyBot>(MeshComp->GetOwner());

		if (Player != nullptr)
			Player->PlaySound("FootStep"); // 플레이어일 경우 발소리 출력
		else if (Bot != nullptr)
			Bot->PlaySound("FootStep"); // 몬스터일 경우 발소리 출력
	}
}

void UMyFootStepAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{

}