// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStartSoundAnimNotifyState.h"
#include "MyBasicCharacter.h"


void UMyStartSoundAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
			Player->PlaySound("StartVoice"); // �÷��̾��� ���� ��Ҹ� ���
	}
}

void UMyStartSoundAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
			Player->PlaySound("StartWeapon"); // �÷��̾��� ��� �߼Ҹ� ���
	}
}