// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD_UI.h"
#include "AController_StartMenu.h"
#include "GameFramework/PlayerController.h"
#include "BasicCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Containers/UnrealString.h"

void UGameHUD_UI::NativeConstruct()
{
	
	//////////////* 버튼 <-> 함수 바인딩 */////////////

	if (Btn_GameMenu)
	{
		Btn_GameMenu->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_GameMenu_Clicked);
	}

	if (Btn_Inventory)
	{
		Btn_Inventory->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_Inventory_Clicked);
	}
	
	if (Btn_Attack)
	{
		Btn_Attack->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_Attack_Clicked);
	}

	if (Btn_ChangeWeapon)
	{
		Btn_ChangeWeapon->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_ChangeWeapon_Clicked);
	}

	if (Btn_Skill1)
	{
		Btn_Skill1->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_Skill1_Clicked);
	}

	if (Btn_Skill2)
	{
		Btn_Skill2->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_Skill2_Clicked);
	}
}


// Progress Bar 채워진 비율 할당
void UGameHUD_UI::set_HUDbar_value_percent(float const HP, float const MP, float const EXP) 
{
	HUD_HPbar_value->SetPercent(HP);
	HUD_MPbar_value->SetPercent(MP);
	HUD_EXPbar_value->SetPercent(EXP);
}

//////////////////////////////////////////////////////////////////////////
/////////////////* 버튼 클릭에 따라 호출되는 함수 정의 */////////////////
//////////////////////////////////////////////////////////////////////////

void UGameHUD_UI::Btn_GameMenu_Clicked()
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->ShowGameMenu();
}

void UGameHUD_UI::Btn_Inventory_Clicked()
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->ShowInventory();
}

void UGameHUD_UI::Btn_Attack_Clicked()
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->WeaponAttack();
}

void UGameHUD_UI::Btn_ChangeWeapon_Clicked()
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->ChangeWeapon();
}

void UGameHUD_UI::Btn_Skill1_Clicked()
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->Skill1();
}

void UGameHUD_UI::Btn_Skill2_Clicked()
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->Skill2();
}