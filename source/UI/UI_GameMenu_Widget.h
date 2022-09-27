// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

#include "UI_GameMenu_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_GameMenu_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* LevelText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* AttackPowerText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MaxHPText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MaxMPText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MaxEXPText = nullptr;

	///////////////* Skill1 TextBlock */////////////////

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Skill1_MP_Text = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Skill1_Activation_Lv_Text = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Skill1_AttackPower_Text = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Skill1_CoolTime_Text = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GameMenu_Close = nullptr; // 게임 메뉴 버튼


	UFUNCTION()
		void Btn_GameMenu_CloseWindow();

private:
	
};
