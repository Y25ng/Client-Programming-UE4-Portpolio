// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "BasicCharacter.h"
#include "UI_CharacterName_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_CharacterName_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_OK = nullptr; // ĳ���� �̸� �Է� Ȯ��

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* Input_CharacterName; // ������ ���1 ���� ���� �Է� 

	ABasicCharacter* Player; // �÷��̾�
	
protected:

	UFUNCTION()
		void Btn_OK_Func(); // OK ��ư�� ���� �� ���� �� �Լ�
};
