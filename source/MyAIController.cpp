// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"

#include "Kismet/GameplayStatics.h"

#include "BehaviorTree/BehaviorTreecomponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h" // AI 인식을 위한 라이브러리
#include "Perception/AISenseConfig_Sight.h" // AI 시야를 위한 라이브러리
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Engine.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

AMyAIController::AMyAIController(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;

	behavior_tree_Comp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp")); // 비헤이비어트리 객체 생성
	blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp")); // 블랙보드 객체 생성

	Setup_Perception_System();  // AI Pawn 기본 능력에 대한 초기화
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyAIController::OnPossess(APawn* InPawn) // Pawn이 AI 컨트롤러를 가지게 하는 함수
{
	Super::OnPossess(InPawn);

	AMyBot* Bot = Cast<AMyBot>(InPawn);

	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset); // 블랙보드 초기화
		}
		behavior_tree_Comp->StartTree(*(Bot->BotBehavior)); // 비헤이비어트리 작동 시작
	}
}

FRotator AMyAIController::GetControlRotation() const // 현재 회전값 반환
{
	if (GetPawn() == nullptr)
		return FRotator(0.f, 0.f, 0.f);

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);
}

void AMyAIController::On_Target_Detected(AActor* actor, FAIStimulus const stimulus) // 타켓을 감지시 실행
{
	if (auto const ch = Cast<AMyBasicCharacter>(actor)) // 시야에 들어온 Pawn이 플레이어 캐릭터일시 실행
	{
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed()); 
		// 블랙보드에서 타겟이 시야에 있는지에 대한 여부를 나타내는 bool 함수를 true로 할당
	}
}

UBlackboardComponent* AMyAIController::get_blackboard() const // 블랙보드 반환 함수
{
	return blackboard;
}

void AMyAIController::Setup_Perception_System() // AI Pawn 기본 능력에 대한 초기화
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
