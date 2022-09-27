// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFootStepAnimNotifyState.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"

void UMyFootStepAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(MeshComp->GetOwner());
		AMyBot* Bot = Cast<AMyBot>(MeshComp->GetOwner());

		if (Player != nullptr)
			Player->PlaySound("FootStep"); // �÷��̾��� ��� �߼Ҹ� ���
		else if (Bot != nullptr)
			Bot->PlaySound("FootStep"); // ������ ��� �߼Ҹ� ���
	}
}

void UMyFootStepAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{

}