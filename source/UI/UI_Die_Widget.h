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
		class USoundCue* BGMSound; // �������

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GotoLobby = nullptr; // ����ȭ������ ���ư� ��ư

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_StartNewGame = nullptr; // ���� ����� ��ư


	UFUNCTION()
		void GotoLobby(); // ����ȭ������ ���ư��� �Լ�

	UFUNCTION()
		void StartNewGame(); // ������ ����� �ϴ� �Լ�
};
