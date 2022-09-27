// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI_GameLoby_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AUI_GameLoby_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AUI_GameLoby_HUD();
	void BeginPlay()override;

private:
	TSubclassOf<class UUserWidget>uiBPClass;
	UUserWidget* uiWidget;
};
