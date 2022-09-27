// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StartMenu_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AStartMenu_HUD : public AHUD
{
	GENERATED_BODY()

public:
	AStartMenu_HUD();
	virtual void BeginPlay()override;

private:
	TSubclassOf<class UUserWidget>uiBPClass;
	UUserWidget* uiWidget;
	
};
