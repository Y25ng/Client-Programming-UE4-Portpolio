// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "StartMenu_UI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UStartMenu_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_StartGame = nullptr; // 게임 시작 버튼

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ExitGame = nullptr; // 게임 나가기 버튼

private:
	UFUNCTION()
		void Btn_StartGame_Clicked(); // 게임 시작 버튼 클릭 시 호출

	UFUNCTION()
		void Btn_ExitGame_Clicked(); // 게임 나가기 버튼 클릭 시 호출

	FString SaveSlotName;
};