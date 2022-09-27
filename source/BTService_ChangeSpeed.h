// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChangeSpeed.generated.h"

/**
 * 
 */

// BTService : Task와 비슷 -> 차이점? 지속적으로 interval을 정해 개입

UCLASS()
class MYPROJECT2_API UBTService_ChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ChangeSpeed();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;

protected:
	FString GetStaticServiceDescription() const override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float speed = 500.0f; // 바꿔줄 속도 
	
};
