// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameLoby_HUD.h"

#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AUI_GameLoby_HUD::AUI_GameLoby_HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>ui(TEXT("/Game/Blueprints/UI/BP_GameLoby_Widget"));
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class;
	}
}
void AUI_GameLoby_HUD::BeginPlay()
{
	Super::BeginPlay();
	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}
	}
}