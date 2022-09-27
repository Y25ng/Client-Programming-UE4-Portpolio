// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LevelSelect_Widget.h"

#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HorizontalBox.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Engine.h"
#include "MyBasicCharacter.h"
#include "Gateway.h"
#include "AController_StartMenu.h"
#include "Gateway.h"

void UUI_LevelSelect_Widget::NativeConstruct()
{

	if (Btn_Level_1_Select)
	{
		Btn_Level_1_Select->OnClicked.AddDynamic(this, &UUI_LevelSelect_Widget::Btn_Level_1_Select_Action);
		// 레벨 2 던전으로 들어가는 버튼을 누를 시 해당하는 함수 호출
	}

	if (Btn_Level_2_Select)
	{
		Btn_Level_2_Select->OnClicked.AddDynamic(this, &UUI_LevelSelect_Widget::Btn_Level_2_Select_Action);
		// 레벨 2 던전으로 들어가는 버튼을 누를 시 해당하는 함수 호출
	}
}

void UUI_LevelSelect_Widget::Btn_Level_1_Select_Action() // 레벨 1 던전으로 들어가는 함수
{
	if (Player)
	{
		auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(Player->GetSaveSlotName(), 0));
		MySaveGameData->DungeonLevel = 1;
		UGameplayStatics::SaveGameToSlot(MySaveGameData, Player->GetSaveSlotName(), 0);

		Btn_Level_1_Select->OnClicked.AddDynamic(this, &UUI_LevelSelect_Widget::Btn_Level_1_Select_Action);
		// 레벨 1 던전으로 들어가는 버튼을 누를 시 해당하는 함수 호출

		UGameplayStatics::OpenLevel(GetWorld(), "/Game/InfinityBladeGrassLands/Maps/ElvenRuins");
	}	
}

void UUI_LevelSelect_Widget::Btn_Level_2_Select_Action() // 레벨 2 던전으로 들어가는 함수
{
	if (Player)
	{
		Player->CurrentDungeon = Player->DungeonDataTable->FindRow<FDungeonClearReward>(*FString::FromInt(1), TEXT(""));

		if (Player->CurrentDungeon->bDungeonClear == false)
			return;

		auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(Player->GetSaveSlotName(), 0));
		MySaveGameData->DungeonLevel = 2;
		UGameplayStatics::SaveGameToSlot(MySaveGameData, Player->GetSaveSlotName(), 0);

		UGameplayStatics::OpenLevel(GetWorld(), "/Game/InfinityBladeIceLands/Maps/FrozenCove");
	}
}