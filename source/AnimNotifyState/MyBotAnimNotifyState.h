// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BasicCharacter.h"
#include "MyBotAnimNotifyState.generated.h"

/**
 * 적 공격 애니메이션이 동작할 때 -> 특정 구간에서만 데미지를 입힐 수 있게 하기 위하여
 */

UCLASS()
class MYPROJECT2_API UMyBotAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // 지정 구간의 Begin 지점에서 실행
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // 지정 구간의 End 지점에서 실행

	void AttackEndExcute();
};
