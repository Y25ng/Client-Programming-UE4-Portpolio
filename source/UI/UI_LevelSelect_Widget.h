// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "MyBasicCharacter.h"
#include "AController_StartMenu.h"
#include "Gateway.h"
#include "UI_LevelSelect_Widget.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_LevelSelect_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	AMyBasicCharacter* Player;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Level_1_Select = nullptr; // 레벨 1 던전으로 입장하는 버튼

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Level_2_Select = nullptr; // 레벨 2 던전으로 입장하는 버튼

	UFUNCTION()
		void Btn_Level_1_Select_Action(); // 레벨 1 던전으로 입장하는 함수
	UFUNCTION()
		void Btn_Level_2_Select_Action(); // 레벨 2 던전으로 입장하는 함수
};
