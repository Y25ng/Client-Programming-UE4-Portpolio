// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AStartMenu_HUD::AStartMenu_HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>ui(TEXT("/Game/Blueprints/UI/BP_StartMenu"));
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class; // 게임 시작 위젯을 가져옴
	}
}

void AStartMenu_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		if (uiWidget)
		{
			uiWidget->AddToViewport(); // 게임 시작 위젯을 화면에 출력
		}
	}
}