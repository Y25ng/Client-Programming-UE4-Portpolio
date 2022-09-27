// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Shop_Widget.h"

void UUI_Shop_Widget::NativeConstruct()
{
	if (Btn_Buy_Item1)
	{
		Btn_Buy_Item1->OnClicked.AddDynamic(this, &UUI_Shop_Widget::Btn_Buy_Item1_Func);
		// ������ ���1 ���� �Լ� ȣ��
	}
	if (Btn_Buy_Item2)
	{
		Btn_Buy_Item2->OnClicked.AddDynamic(this, &UUI_Shop_Widget::Btn_Buy_Item2_Func);
		// ������ ���2 ���� �Լ� ȣ��
	}
}

void UUI_Shop_Widget::Btn_Buy_Item1_Func()
{
	FString tempStr = (InputItem1->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*tempStr);

	if (tempCnt > 0)
	{
		NPCBot->BuyItem1(tempCnt);
	}
}

void UUI_Shop_Widget::Btn_Buy_Item2_Func()
{
	FString tempStr = (InputItem2->GetText()).ToString();
	int32 tempCnt = FCString::Atoi(*tempStr);

	if (tempCnt > 0)
	{
		NPCBot->BuyItem2(tempCnt);
	}
}

