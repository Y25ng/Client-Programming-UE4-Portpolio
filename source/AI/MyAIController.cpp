// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"

#include "Kismet/GameplayStatics.h"

#include "BehaviorTree/BehaviorTreecomponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h" // AI �ν��� ���� ���̺귯��
#include "Perception/AISenseConfig_Sight.h" // AI �þ߸� ���� ���̺귯��
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Engine.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

AMyAIController::AMyAIController(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;

	behavior_tree_Comp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp")); // �����̺��Ʈ�� ��ü ����
	blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp")); // ������ ��ü ����

	Setup_Perception_System();  // AI Pawn �⺻ �ɷ¿� ���� �ʱ�ȭ
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyAIController::OnPossess(APawn* InPawn) // Pawn�� AI ��Ʈ�ѷ��� ������ �ϴ� �Լ�
{
	Super::OnPossess(InPawn);

	AMyBot* Bot = Cast<AMyBot>(InPawn);

	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset); // ������ �ʱ�ȭ
		}
		behavior_tree_Comp->StartTree(*(Bot->BotBehavior)); // �����̺��Ʈ�� �۵� ����
	}
}

FRotator AMyAIController::GetControlRotation() const // ���� ȸ���� ��ȯ
{
	if (GetPawn() == nullptr)
		return FRotator(0.f, 0.f, 0.f);

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);
}

void AMyAIController::On_Target_Detected(AActor* actor, FAIStimulus const stimulus) // Ÿ���� ������ ����
{
	if (auto const ch = Cast<AMyBasicCharacter>(actor)) // �þ߿� ���� Pawn�� �÷��̾� ĳ�����Ͻ� ����
	{
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed()); 
		// �����忡�� Ÿ���� �þ߿� �ִ����� ���� ���θ� ��Ÿ���� bool �Լ��� true�� �Ҵ�
	}
}

UBlackboardComponent* AMyAIController::get_blackboard() const // ������ ��ȯ �Լ�
{
	return blackboard;
}

void AMyAIController::Setup_Perception_System() // AI Pawn �⺻ �ɷ¿� ���� �ʱ�ȭ
{
	Sight_Config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	Sight_Config->SightRadius = AISightRadius;
	Sight_Config->LoseSightRadius = AILoseSightRadius;
	Sight_Config->PeripheralVisionAngleDegrees = AIFieldOfView;
	Sight_Config->SetMaxAge(AISightAge);
	Sight_Config->AutoSuccessRangeFromLastSeenLocation = 520.f;
	Sight_Config->DetectionByAffiliation.bDetectEnemies = true;
	Sight_Config->DetectionByAffiliation.bDetectFriendlies = true;
	Sight_Config->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*Sight_Config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::On_Target_Detected);
	GetPerceptionComponent()->ConfigureSense(*Sight_Config);
}
