// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"


/** AI ���� ���̺귯��*/
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

// nav mesh bounds volume�� ���� AI�� �۵��� ���� �������ֱ�

// �����̺�� Ʈ�� : AI ���μ��� 
// ������ : ���μ��� �۵��� �������� ���� Ȯ���ذ��� ����

UCLASS(config = Game)
class MYPROJECT2_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController(FObjectInitializer const& object_initializer);

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;  // Pawn�� AI Controller�� ������ �ϴ� �Լ�
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override; // Pawn�� FRotator ������ ��ȯ 

	UFUNCTION()
		void On_Target_Detected(AActor* actor, FAIStimulus const stimulus); // Ÿ���� ������ ����

	class UBlackboardComponent* get_blackboard() const; // ������ ��ȯ �Լ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.f; // AI �þ� �Ÿ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.f; // AI�� �þ� �ð�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.f; // AI���� �Ⱥ��̴� �Ÿ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 180.f; // �¿� �þ߰�

	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected = false; // �� ĳ���͸� ã�Ҵ��� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f; // �� ĳ���Ϳ��� �Ÿ�

private:

	//UPROPERTY(transient)
		//UBlackboardComponent* BlackboardComp; // ������ ������Ʈ
	//UPROPERTY(transient)
		//UBehaviorTreeComponent* BehaviorComp; // �����̺��Ʈ�� ������Ʈ

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp; // �����̺��Ʈ�� ���۳�Ʈ
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree; // �����̺��Ʈ��

	class UBlackboardComponent* blackboard; // ������
	class UAISenseConfig_Sight* Sight_Config; // �þ߿� ���� ����

	void Setup_Perception_System(); // AI Pawn �⺻ �ɷ¿� ���� �ʱ�ȭ
};
