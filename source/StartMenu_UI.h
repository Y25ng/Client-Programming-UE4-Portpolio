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
		UButton* Btn_StartGame = nullptr; // ���� ���� ��ư

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ExitGame = nullptr; // ���� ������ ��ư

private:
	UFUNCTION()
		void Btn_StartGame_Clicked(); // ���� ���� ��ư Ŭ�� �� ȣ��

	UFUNCTION()
		void Btn_ExitGame_Clicked(); // ���� ������ ��ư Ŭ�� �� ȣ��

	FString SaveSlotName;
};