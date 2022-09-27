// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_InGame.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AHUD_InGame : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUD_InGame();
	void BeginPlay()override;

private:
		TSubclassOf<class UUserWidget> uiBPClass; // 타입을 UUserWidget으로 제한
		class UUserWidget* uWidget; // 가지고 있는 위젯

};
