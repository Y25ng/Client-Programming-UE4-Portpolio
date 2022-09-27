// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyBotHitAnimNotifyState.generated.h"

/**
 * 적의 피격 액션이 동작할 때 사용 -> 적의 피격 액션이 동작하는 중에는 다른 동작이 불가능하게끔 구현
 */
UCLASS()
class MYPROJECT2_API UMyBotHitAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // 지정 구간의 Begin 지점에서 실행
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // 지정 구간의 End 지점에서 실행
};
