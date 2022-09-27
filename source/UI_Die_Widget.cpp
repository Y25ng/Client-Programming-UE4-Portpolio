// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Die_Widget.h"
#include "Kismet/GameplayStatics.h"
#include "AController_StartMenu.h"
#include "Engine.h"

void UUI_Die_Widget::NativeConstruct()
{
	if (Btn_GotoLobby)
	{
		Btn_GotoLobby->OnClicked.AddDynamic(this, &UUI_Die_Widget::GotoLobby); // 시작화면으로 돌아가는 버튼을 클릭 시 해당 함수 호출
	}

	if (Btn_StartNewGame)
	{
		Btn_StartNewGame->OnClicked.AddDynamic(this, &UUI_Die_Widget::StartNewGame); // 새로운 게임 시작 버튼
	}
}

void UUI_Die_Widget::GotoLobby() // 시작화면으로 돌아가는 버튼을 누를 시 호출 될 함수
{
	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(Player->GetSaveSlotName(), 0));
	MySaveGameData->DungeonLevel = 0;
	UGameplayStatics::SaveGameToSlot(MySaveGameData, Player->GetSaveSlotName(), 0);

	UGameplayStatics::OpenLevel(this, "/Game/EnvironmentPack3/Maps/DemoMap1");
}

void UUI_Die_Widget::StartNewGame() // 새로운 게임 시작 버튼을 누를 시 호출 될 함수
{
	int32 TempDungeonLv = Player->GetDungeonLevel();

	//auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(Player->GetSaveSlotName(), 0));
	//TempDungeonLv = MySaveGameData->DungeonLevel;

	if (TempDungeonLv == 0)
		UGameplayStatics::OpenLevel(this, "/Game/EnvironmentPack3/Maps/DemoMap1");
	else if (TempDungeonLv == 1)
		UGameplayStatics::OpenLevel(this, "/Game/InfinityBladeGrassLands/Maps/ElvenRuins");
	else if (TempDungeonLv == 2)
		UGameplayStatics::OpenLevel(this, "/Game/InfinityBladeIceLands/Maps/FrozenCove");
}

