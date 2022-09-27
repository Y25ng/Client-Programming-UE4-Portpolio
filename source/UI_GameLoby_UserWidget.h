// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "UI_GameLoby_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_GameLoby_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;


protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_CheckReward = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GotoLobby = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_StartNextGame = nullptr;

	UFUNCTION()
		void Btn_StageInfo_CloseWindow();

	UFUNCTION()
		void GotoLobby();

	UFUNCTION()
		void StartNextGame();
	
};
