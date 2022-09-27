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
		AMyNPCbot* NPCBot; // 판매상 Pawn

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Buy_Item1 = nullptr; // 아이템 목록1 구매 버튼

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Buy_Item2 = nullptr; // 아이템 목록2 구매 버튼

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* InputItem1; // 아이템 목록1 구매 개수 입력 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* InputItem2; // 아이템 목록2 구매 개수 입력 
protected:

	UFUNCTION()
		void Btn_Buy_Item1_Func(); // 인벤토리 닫기 버튼 누를 시 호출 될 함수

	UFUNCTION()
		void Btn_Buy_Item2_Func(); // 인벤토리 닫기 버튼 누를 시 호출 될 함수

};
