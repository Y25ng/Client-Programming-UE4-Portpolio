// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AGameHUD_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AGameHUD_HUD();
	void BeginPlay()override;

};
