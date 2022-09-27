// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameLoby_UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UUI_GameLoby_UserWidget::NativeConstruct()
{
	if (Btn_CheckReward)
	{
		Btn_CheckReward->OnClicked.AddDynamic(this, &UUI_GameLoby_UserWidget::GotoLobby);
	}

	if (Btn_GotoLobby)
	{
		Btn_GotoLobby->OnClicked.AddDynamic(this, &UUI_GameLoby_UserWidget::GotoLobby);
	}

	if (Btn_StartNextGame)
	{
		Btn_StartNextGame->OnClicked.AddDynamic(this, &UUI_GameLoby_UserWidget::StartNextGame);
	}

}

void UUI_GameLoby_UserWidget::Btn_StageInfo_CloseWindow()
{

}

void UUI_GameLoby_UserWidget::GotoLobby()
{
	UGameplayStatics::OpenLevel(this, "/Game/StartMenu_Level");
}

void UUI_GameLoby_UserWidget::StartNextGame()
{
	UGameplayStatics::OpenLevel(this, "/Game/Level02");
}