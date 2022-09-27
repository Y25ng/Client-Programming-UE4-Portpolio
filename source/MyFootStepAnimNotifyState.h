// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyFootStepAnimNotifyState.generated.h"

/**
 * ���ڱ� �Ҹ� ������ ���� 
 */

UCLASS()
class MYPROJECT2_API UMyFootStepAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // ���� ������ Begin �������� ����
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // ���� ������ End �������� ����
};
