// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"


/** AI 관련 라이브러리*/
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

#include "Perception/AIPerceptionTypes.h"

#include "MyAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
/**
 * 
 */

// nav mesh bounds volume을 통해 AI가 작동할 구역 설정해주기

// 비헤이비어 트리 : AI 프로세스 
// 블랙보드 : 프로세스 작동시 블랙보드의 값을 확인해가며 실행

UCLASS(config = Game)
class MYPROJECT2_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController(FObjectInitializer const& object_initializer);

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;  // Pawn이 AI Controller를 가지게 하는 함수
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override; // Pawn의 FRotator 정보를 반환 

	UFUNCTION()
		void On_Target_Detected(AActor* actor, FAIStimulus const stimulus); // 타켓을 감지시 실행

	class UBlackboardComponent* get_blackboard() const; // 블랙보드 반환 함수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.f; // AI 시야 거리
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.f; // AI의 시야 시간
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.f; // AI에게 안보이는 거리
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 180.f; // 좌우 시야각

	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected = false; // 적 캐릭터를 찾았는지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f; // 적 캐릭터와의 거리

private:

	//UPROPERTY(transient)
		//UBlackboardComponent* BlackboardComp; // 블랙보드 컴포넌트
	//UPROPERTY(transient)
		//UBehaviorTreeComponent* BehaviorComp; // 비헤이비어트리 컴포넌트

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp; // 비헤이비어트리 컴퍼넌트
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree; // 비헤이비어트리

	class UBlackboardComponent* blackboard; // 블랙보드
	class UAISenseConfig_Sight* Sight_Config; // 시야에 대한 변수

	void Setup_Perception_System(); // AI Pawn 기본 능력에 대한 초기화
};
