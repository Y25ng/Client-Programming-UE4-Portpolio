// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_DungeonReward_Widget.h"
#include "Kismet/GameplayStatics.h"
#include "BasicCharacter.h"

void UUI_DungeonReward_Widget::NativeConstruct()
{
	if (Btn_GotoLobby)
	{
		Btn_GotoLobby->OnClicked.AddDynamic(this, &UUI_DungeonReward_Widget::GotoLobby); // 시작화면으로 돌아가는 버튼을 클릭 시 해당 함수 호출
	}
}

void UUI_DungeonReward_Widget::GotoLobby() // 시작화면으로 돌아가는 버튼을 누를 시 호출 될 함수
{
	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(Player->GetSaveSlotName(), 0));
	MySaveGameData->DungeonLevel = 0;
	UGameplayStatics::SaveGameToSlot(MySaveGameData, Player->GetSaveSlotName(), 0);

	UGameplayStatics::OpenLevel(this, "/Game/EnvironmentPack3/Maps/DemoMap1");
}