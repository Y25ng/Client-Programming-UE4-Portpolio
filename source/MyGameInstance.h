// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h" // ���������̺� ��� ���̺귯��

#include "MyGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FCharacterData() : Level(1), MaxHP(100.0f), MaxMP(50.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 NextExp;
};

UCLASS()
class MYPROJECT2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

public:
	FCharacterData* GetCharacterData(int32 Level);

private:
	UPROPERTY()
		class UDataTable* CharacterTable;
};
