// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyBombAnimNotifyState.generated.h"

/**
 * 폭탄을 던지는 적의 공격 애니메이션이 동작할 때 -> 폭탄이 던져지는 타이밍을 지정하기 위해 사용
 */
UCLASS()
class MYPROJECT2_API UMyBombAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // 지정 구간의 Begin 지점에서 실행
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // 지정 구간의 End 지점에서 실행
};
