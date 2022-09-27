// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h" // Progressbar 이용을 위한 라이브러리
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
	void set_bar_value_percent(float const value); // 캐릭터의 hp value를 HPPar(progress bar)에 값을 퍼센트화
	void set_Level_TextBlock(int32 const value); // 몬스터 표시할 레벨을 설정

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HPBar_Value = nullptr; // Wiget 컴포넌트의 Progressbar와 연결

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Level_TextBlock = nullptr;
};
