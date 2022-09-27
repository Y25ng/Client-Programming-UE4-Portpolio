// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_BoosterGage_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UUI_BoosterGage_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void set_bar_value_percent(float const value); // 캐릭터의 부스터 게이지 value를 부스터게이지바(progress bar)에 값을 퍼센트화

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* BoosterGageBar_Value = nullptr; // Wiget 컴포넌트의 Progressbar와 연결
};
