// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_UI.h"
#include "MySaveGame.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UStartMenu_UI::NativeConstruct()
{

	if (Btn_StartGame)
	{
		Btn_StartGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Btn_StartGame_Clicked); // ��ư�� ���� �� �ش� �Լ� ����
	}

	if (Btn_ExitGame)
	{
		Btn_ExitGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Btn_ExitGame_Clicked); // ��ư�� ���� �� �ش� �Լ� ����
	}

	SaveSlotName = TEXT("Player1");
}


void UStartMenu_UI::Btn_StartGame_Clicked()
{

	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	if (MySaveGameData == nullptr)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/EnvironmentPack3/Maps/DemoMap1");
	}
	else
	{
		int32 TempDungeonLv = MySaveGameData->DungeonLevel;

		if(TempDungeonLv == 0)
			UGameplayStatics::OpenLevel(GetWorld(), "/Game/EnvironmentPack3/Maps/DemoMap1");
		else if (TempDungeonLv == 1)
			UGameplayStatics::OpenLevel(this, "/Game/InfinityBladeGrassLands/Maps/ElvenRuins");
		else if (TempDungeonLv == 2)
			UGameplayStatics::OpenLevel(this, "/Game/InfinityBladeIceLands/Maps/FrozenCove");
	}
	// Start ��ư�� ������ ���� ������ �̵�
}

void UStartMenu_UI::Btn_ExitGame_Clicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	// Exit ��ư�� ������ ������ ����
}