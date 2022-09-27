// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBotAnimNotifyState.generated.h"

/**
 * �� ���� �ִϸ��̼��� ������ �� -> Ư�� ���������� �������� ���� �� �ְ� �ϱ� ���Ͽ�
 */

UCLASS()
class MYPROJECT2_API UMyBotAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // ���� ������ Begin �������� ����
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // ���� ������ End �������� ����

	void AttackEndExcute();
};