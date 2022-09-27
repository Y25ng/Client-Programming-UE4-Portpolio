// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyCharacterStatComponent::UMyCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UMyCharacterStatComponent::BeginPlay()
{
	UActorComponent::BeginPlay();

	// ...
	
}

void UMyCharacterStatComponent::InitializeComponent()
{
	UActorComponent::InitializeComponent();
	SetNewLevel(Level);
}

void UMyCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(GameInstance != nullptr)
		CurrentStatData = GameInstance->GetCharacterData(NewLevel);

	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
		SetMP(CurrentStatData->MaxMP);
		SetExp(0.0f);
	}
}

int32 UMyCharacterStatComponent::GetMyLevel()
{
	return Level;
}

void UMyCharacterStatComponent::SetDamage(float NewDamage)
{
	if(CurrentStatData != nullptr)
		SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

void UMyCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	// OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		// OnHPIsZero.Broadcast();
	}
}

float UMyCharacterStatComponent::GetMaxHP()
{
	return CurrentStatData->MaxHP;
}

float UMyCharacterStatComponent::GetHP()
{
	return CurrentHP;
}

void UMyCharacterStatComponent::SetMP(float NewMP)
{
	CurrentMP = NewMP;
	// OnMPChanged.Broadcast();
	if (CurrentMP < KINDA_SMALL_NUMBER)
	{
		CurrentMP = 0.0f;
		// OnMPIsZero.Broadcast();
	}
}

float UMyCharacterStatComponent::GetMaxMP()
{
	return CurrentStatData->MaxMP;
}

float UMyCharacterStatComponent::GetMP()
{
	return CurrentMP;
}

void UMyCharacterStatComponent::SetExp(float NewExp)
{
	CurrentExp = NewExp;
	// OnExpChanged.Broadcast();
}

float UMyCharacterStatComponent::GetMaxExp()
{
	return CurrentStatData->NextExp;
}

float UMyCharacterStatComponent::GetExp()
{
	return CurrentExp;
}


float UMyCharacterStatComponent::GetAttack()
{
	if (CurrentStatData != nullptr)
		return 0.0f;

	return CurrentStatData->Attack;
}

float UMyCharacterStatComponent::GetHPRatio()
{
	if (CurrentStatData != nullptr)
		return 0.0f;

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

float UMyCharacterStatComponent::GetMPRatio()
{
	if (CurrentStatData != nullptr)
		return 0.0f;

	return (CurrentStatData->MaxMP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentMP / CurrentStatData->MaxMP);
}

// Called every frame
void UMyCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}