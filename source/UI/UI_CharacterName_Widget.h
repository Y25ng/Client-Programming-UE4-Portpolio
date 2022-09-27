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
		UButton* Btn_OK = nullptr; // 캐릭터 이름 입력 확인

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* Input_CharacterName; // 아이템 목록1 구매 개수 입력 

	ABasicCharacter* Player; // 플레이어
	
protected:

	UFUNCTION()
		void Btn_OK_Func(); // OK 버튼을 누를 시 실행 될 함수
};
