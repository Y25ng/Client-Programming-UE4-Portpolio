// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBar.h"
#include "GameHUD_UI.h"

void UHPBar::NativeConstruct()
{

}

void UHPBar::set_bar_value_percent(float const value)
{
	HPBar_Value->SetPercent(value); // 캐릭터의 hp value를 HPPar( progress bar )에 받아 값을 퍼센트화 
}

void UHPBar::set_Level_TextBlock(int32 const value)
{
	Level_TextBlock->SetText(FText::FromString(*FString::FromInt(value))); // 캐릭터의 hp value를 HPPar( progress bar )에 받아 값을 퍼센트화 
}
