// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"

UMyGameInstance::UMyGameInstance()
{
    FString CharacterDataPath = TEXT("/Game/Data/MyCharacter_DataTable_2.MyCharacter_DataTable_2");
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*CharacterDataPath);
    if(DT_ABCHARACTER.Succeeded())
        CharacterTable = DT_ABCHARACTER.Object;

    // CharacterTable->GetRowMap().Num() > 0
}

void UMyGameInstance::Init()
{
    Super::Init();
    // ABLOG_S(Warning);
}

FCharacterData* UMyGameInstance::GetCharacterData(int32 Level)
{
    return CharacterTable->FindRow<FCharacterData>(*FString::FromInt(Level), TEXT(""));
}