// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStartSoundAnimNotifyState.h"
#include "MyBasicCharacter.h"


void UMyStartSoundAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
			Player->PlaySound("StartVoice"); // 플레이어의 시작 목소리 출력
	}
}

void UMyStartSoundAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
			Player->PlaySound("StartWeapon"); // 플레이어일 경우 발소리 출력
	}
}