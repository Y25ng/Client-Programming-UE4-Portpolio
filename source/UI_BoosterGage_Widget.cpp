// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_BoosterGage_Widget.h"

void UUI_BoosterGage_Widget::NativeConstruct()
{

}

void UUI_BoosterGage_Widget::set_bar_value_percent(float const value)
{
	BoosterGageBar_Value->SetPercent(value); // 캐릭터의 부스터 게이지를 부스터게이지바( progress bar )에 받아 값을 퍼센트화 
}