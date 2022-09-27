// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BasicCharacter.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMySaveGame();

	UPROPERTY()
		int32 Level;

	UPROPERTY()
		int32 Gold;

	UPROPERTY()
		float Exp;

	UPROPERTY()
		FString PlayerName;

	UPROPERTY()
		int32 DungeonLevel;

	UPROPERTY()
		TMap<FString, int32> ItemCntMap;

	UPROPERTY()
		TArray<bool> DungeonClear;
};
