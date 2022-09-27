// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameMenu_Widget.h"
#include "AController_StartMenu.h"
#include "MyBasicCharacter.h"
#include "Kismet/GameplayStatics.h"

void UUI_GameMenu_Widget::NativeConstruct()
{
	if (Btn_GameMenu_Close) 
	{
		Btn_GameMenu_Close->OnClicked.AddDynamic(this, &UUI_GameMenu_Widget::Btn_GameMenu_CloseWindow); // �޴� �ݱ� ��ư�� �������� �ش� �Լ��� ����
	}
}

void UUI_GameMenu_Widget::Btn_GameMenu_CloseWindow() // �޴� �ݱ� ��ư�� ������ �� ȣ��� �Լ�
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->CloseGameMenu();
}