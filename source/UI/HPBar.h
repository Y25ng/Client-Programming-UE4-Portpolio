// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h" // Progressbar �̿��� ���� ���̺귯��
#include "Runtime/UMG/Public/Components/TextBlock.h"

#include "HPBar.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UHPBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void set_bar_value_percent(float const value); // ĳ������ hp value�� HPPar(progress bar)�� ���� �ۼ�Ʈȭ
	void set_Level_TextBlock(int32 const value); // ���� ǥ���� ������ ����

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HPBar_Value = nullptr; // Wiget ������Ʈ�� Progressbar�� ����

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Level_TextBlock = nullptr;
};
