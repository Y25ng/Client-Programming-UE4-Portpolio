// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterName_Widget.h"

void UUI_CharacterName_Widget::NativeConstruct()
{
	if (Btn_OK)
	{
		Btn_OK->OnClicked.AddDynamic(this, &UUI_CharacterName_Widget::Btn_OK_Func);
	}
}

void UUI_CharacterName_Widget::Btn_OK_Func()
{
	FString tempStr = (Input_CharacterName->GetText()).ToString();

	Player->SetNickName(tempStr);
	Player->SaveCharacterStat();
	RemoveFromViewport();
}