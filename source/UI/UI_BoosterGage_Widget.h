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
	void set_bar_value_percent(float const value); // ĳ������ �ν��� ������ value�� �ν��Ͱ�������(progress bar)�� ���� �ۼ�Ʈȭ

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* BoosterGageBar_Value = nullptr; // Wiget ������Ʈ�� Progressbar�� ����
};
