// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_BoosterGage_Widget.h"

void UUI_BoosterGage_Widget::NativeConstruct()
{

}

void UUI_BoosterGage_Widget::set_bar_value_percent(float const value)
{
	BoosterGageBar_Value->SetPercent(value); // ĳ������ �ν��� �������� �ν��Ͱ�������( progress bar )�� �޾� ���� �ۼ�Ʈȭ 
}