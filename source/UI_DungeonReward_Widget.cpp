// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_DungeonReward_Widget.h"
#include "Kismet/GameplayStatics.h"
#include "BasicCharacter.h"

void UUI_DungeonReward_Widget::NativeConstruct()
{
	if (Btn_GotoLobby)
	{
		Btn_GotoLobby->OnClicked.AddDynamic(this, &UUI_DungeonReward_Widget::GotoLobby); // ����ȭ������ ���ư��� ��ư�� Ŭ�� �� �ش� �Լ� ȣ��
	}
}

void UUI_DungeonReward_Widget::GotoLobby() // ����ȭ������ ���ư��� ��ư�� ���� �� ȣ�� �� �Լ�
{
	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(Player->GetSaveSlotName(), 0));
	MySaveGameData->DungeonLevel = 0;
	UGameplayStatics::SaveGameToSlot(MySaveGameData, Player->GetSaveSlotName(), 0);

	UGameplayStatics::OpenLevel(this, "/Game/EnvironmentPack3/Maps/DemoMap1");
}