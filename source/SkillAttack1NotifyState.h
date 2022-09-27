// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SkillAttack1NotifyState.generated.h"

/**
 * 플레이어 스킬1 애니메이션이 동작할 때 -> 특정 구간에서 Particle 효과 출력
										 
 */

UCLASS()
class MYPROJECT2_API USkillAttack1NotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override; // 지정 구간의 Begin 지점에서 실행
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override; // 지정 구간의 End 지점에서 실행
	
};
