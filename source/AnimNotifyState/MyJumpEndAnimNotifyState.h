// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyJumpEndAnimNotifyState.generated.h"

/**
 *  점프 종료 애니메이션중에는 움직일 수 없게 하기 위해 사용되는 AnimNotifyState
 */

UCLASS()
class MYPROJECT2_API UMyJumpEndAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // 지정 구간의 Begin 지점에서 실행
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // 지정 구간의 End 지점에서 실행
};
