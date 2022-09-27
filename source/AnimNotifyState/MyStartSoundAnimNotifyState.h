// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyStartSoundAnimNotifyState.generated.h"

/**
 * �÷��̾� ���� �ִϸ��̼ǿ� ���带 �ֱ� ����
 */
UCLASS()
class MYPROJECT2_API UMyStartSoundAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // ���� ������ Begin �������� ����
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // ���� ������ End �������� ����
	
};
