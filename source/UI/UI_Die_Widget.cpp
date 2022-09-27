// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Die_Widget.h"
#include "Kismet/GameplayStatics.h"
#include "AController_StartMenu.h"
#include "Engine.h"

void UUI_Die_Widget::NativeConstruct()
{
	if (Btn_GotoLobby)
	{
		Btn_GotoLobby->OnClicked.AddDynamic(this, &UUI_Die_Widget::GotoLobby); // ����ȭ������ ���ư��� ��ư�� Ŭ�� �� �ش� �Լ� ȣ��
	}

	if (Btn_StartNewGame)
	{
		Btn_StartNewGame->OnClicked.AddDynamic(this, &UUI_Die_Widget::StartNewGame); // ���ο� ���� ���� ��ư
	}
}

void UUI_Die_Widget::GotoLobby() // ����ȭ������ ���ư��� ��ư�� ���� �� ȣ�� �� �Լ�
{
	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(Player->GetSaveSlotName(), 0));
	MySaveGameData->DungeonLevel = 0;
	UGameplayStatics::SaveGameToSlot(MySaveGameData, Player->GetSaveSlotName(), 0);

	UGameplayStatics::OpenLevel(this, "/Game/EnvironmentPack3/Maps/DemoMap1");
}

void UUI_Die_Widget::StartNewGame() // ���ο� ���� ���� ��ư�� ���� �� ȣ�� �� �Լ�
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

