// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2GameMode.h"
#include "MyProject2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "GameHud_Hud.h"
#include "AController_StartMenu.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h" // UserWidget타입 사용을 위한 라이브러리

AMyProject2GameMode::AMyProject2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> Player(TEXT("/Game/Blueprints/BP_MyBasicCharacter"));
	if (Player.Succeeded())
	{
		DefaultPawnClass = Player.Class;
	}

	HUDClass = AGameHUD_HUD::StaticClass();
	PlayerControllerClass = AAController_StartMenu::StaticClass();
}

void AMyProject2GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Build.cs 파일에 "UMG"를 추가해야 사용가능
	// CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget); // HUDWidget을 CurrentWidget에 담아줌 
	// CurrentWidget -> AddToViewport(); // CurrentWidget을 화면에 출력해줌
}
