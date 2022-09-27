// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGame.h"

UMySaveGame::UMySaveGame()
{
	Level = 1;
	Gold = 10000;
	Exp = 0.f;
	PlayerName = TEXT("Nick Name");
	DungeonLevel = 0;

	for (int32 i = 0; i < 2; i++)
	{
		DungeonClear.Add(false);
	}

	ItemCntMap.Add(TEXT("HP Potion"), 0);
	ItemCntMap.Add(TEXT("MP Potion"), 0);
}
