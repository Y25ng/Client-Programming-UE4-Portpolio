// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "BasicCharacter.h"
#include "UI_DungeonReward_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_DungeonReward_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GotoLobby = nullptr;

	ABasicCharacter* Player;

protected:

	UFUNCTION()
		void GotoLobby(); // 시작화면으로 돌아가는 함수
};
