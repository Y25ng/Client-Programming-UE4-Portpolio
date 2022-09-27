// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasicCharacter.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "UI_Die_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_Die_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	ABasicCharacter* Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* BGMSound; // 배경음악

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GotoLobby = nullptr; // 시작화면으로 돌아갈 버튼

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_StartNewGame = nullptr; // 게임 재시작 버튼


	UFUNCTION()
		void GotoLobby(); // 시작화면으로 돌아가는 함수

	UFUNCTION()
		void StartNewGame(); // 게임을 재시작 하는 함수
};
