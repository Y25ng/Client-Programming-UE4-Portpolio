// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "MyNPCbot.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "UI_Shop_Widget.generated.h"

/**
 * 
 */


UCLASS()
class MYPROJECT2_API UUI_Shop_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AMyNPCbot* NPCBot; // �ǸŻ� Pawn

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Buy_Item1 = nullptr; // ������ ���1 ���� ��ư

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Buy_Item2 = nullptr; // ������ ���2 ���� ��ư

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* InputItem1; // ������ ���1 ���� ���� �Է� 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* InputItem2; // ������ ���2 ���� ���� �Է� 
protected:

	UFUNCTION()
		void Btn_Buy_Item1_Func(); // �κ��丮 �ݱ� ��ư ���� �� ȣ�� �� �Լ�

	UFUNCTION()
		void Btn_Buy_Item2_Func(); // �κ��丮 �ݱ� ��ư ���� �� ȣ�� �� �Լ�

};
