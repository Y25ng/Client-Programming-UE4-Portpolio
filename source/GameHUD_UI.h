// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Components/TextBlock.h"
#include "GameHUD_UI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UGameHUD_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	void set_HUDbar_value_percent(float const HP, float const MP, float const EXP);

	///////////////* (HP, MP, EXP) ProgressBar */////////////////

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HUD_HPbar_value = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HUD_MPbar_value = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HUD_EXPbar_value = nullptr;

	///////////////* (HP, MP, EXP) TextBlock */////////////////

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* HUD_HPbar_Text = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* HUD_MPbar_Text = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* HUD_EXPbar_Text = nullptr;

protected:

	///////////////* Button */////////////////

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GameMenu = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Inventory = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Attack = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ChangeWeapon = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Skill1 = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Skill2 = nullptr;

private:
	
	///////////////* Button 클릭 시 호출할 함수 */////////////////

	UFUNCTION()
		void Btn_GameMenu_Clicked();
	UFUNCTION()
		void Btn_Inventory_Clicked();
	UFUNCTION()
		void Btn_Attack_Clicked();
	UFUNCTION()
		void Btn_ChangeWeapon_Clicked();
	UFUNCTION()
		void Btn_Skill1_Clicked();
	UFUNCTION()
		void Btn_Skill2_Clicked();
};
