// Fill out your copyright notice in the Description page of Project Settings.


#include "Gateway.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/PlayerController.h"
#include "AController_StartMenu.h"
#include "UI_LevelSelect_Widget.h"



// Sets default values
AGateway::AGateway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->InitSphereRadius(150.0f);
	RootComponent = CollisionSphere;

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshObj"));
	mStaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget> LevelSelectUI(TEXT("/Game/Blueprints/UI/BP_Level_Select"));
	if (LevelSelectUI.Succeeded())
	{
		uiLevelSelectBPClass = LevelSelectUI.Class;
	}

	bIsShowLevelSelect = false;
}

// Called when the game starts or when spawned
void AGateway::BeginPlay()
{
	Super::BeginPlay();

	/*
	MyPlayerCharacter = Cast<AMyBasicCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//	tempMapLevel = MyPlayerCharacter->getNextLevel();

	tempStr = "/Game/Level0" + FString::FromInt(RandomGateNum);
	*/
}

void AGateway::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGateway::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // �浹�� Actor�� Player�� ����
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(OtherActor);
		if (Player != nullptr)
		{
			Player->SaveCharacterStat();
			Player->PlaySound("UIOpen"); // ���� ����â ���� ȿ���� ��� 		
		}


		OpenLevelSelect(Player); // ���� ���� ȭ���� ����

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
		GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;
	}
}

void AGateway::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // �浹�� Actor�� Player�� ����
	{
		AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(OtherActor);
		if (Player != nullptr)
		{
			Player->PlaySound("UIClose"); // ���� ����â �ݱ� ȿ���� ��� 		
		}

		CloseLevelSelect(); // ���� ���� ȭ���� ����

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
		GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
	}
}

void AGateway::OpenLevelSelect(AMyBasicCharacter* player) // ���� ���� ȭ���� �����ϴ� �Լ�
{
	if (uiLevelSelectBPClass && bIsShowLevelSelect == false)
	{
		uiLevelSelectWidget = CreateWidget<UUserWidget>(GetWorld(), uiLevelSelectBPClass);
		if (uiLevelSelectWidget)
		{
			Cast<UUI_LevelSelect_Widget>(uiLevelSelectWidget)->Player = player;
			uiLevelSelectWidget->AddToViewport();
		}
		bIsShowLevelSelect = true;
	}
}

void AGateway::CloseLevelSelect() // ���� ���� ȭ���� �����ϴ� �Լ�
{
	uiLevelSelectWidget->RemoveFromViewport();
	bIsShowLevelSelect = false;
}

