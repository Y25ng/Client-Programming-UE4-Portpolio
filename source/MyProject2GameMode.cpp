// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2GameMode.h"
#include "MyProject2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "GameHud_Hud.h"
#include "AController_StartMenu.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h" // UserWidgetŸ�� ����� ���� ���̺귯��

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

	// Build.cs ���Ͽ� "UMG"�� �߰��ؾ� ��밡��
	// CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget); // HUDWidget�� CurrentWidget�� ����� 
	// CurrentWidget -> AddToViewport(); // CurrentWidget�� ȭ�鿡 �������
}
