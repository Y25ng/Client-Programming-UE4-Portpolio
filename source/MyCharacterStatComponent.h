// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "MyGameInstance.h"

#include "MyCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnExpIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnExpChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UMyCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SetNewLevel(int32 NewLevel);

	UFUNCTION()
		int32 GetMyLevel();

	void SetDamage(float NewDamage);

	void SetHP(float NewHP);

	UFUNCTION()
		float GetMaxHP();
	UFUNCTION()
		float GetHP();

	void SetMP(float NewMP);
	UFUNCTION()
		float GetMaxMP();
	UFUNCTION()
		float GetMP();

	void SetExp(float NewExp);
	UFUNCTION()
		float GetMaxExp();
	UFUNCTION()
		float GetExp();

	UFUNCTION()
		float GetAttack();

	UFUNCTION()
		float GetHPRatio();
	UFUNCTION()
		float GetMPRatio();

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnMPIsZeroDelegate OnMPIsZero;
	FOnExpIsZeroDelegate OnExpIsZero;
	FOnHPChangedDelegate OnHPChanged;
	FOnMPChangedDelegate OnMPChanged;
	FOnExpChangedDelegate OnExpChanged;
		
private:
	struct FCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentMP;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentExp;
};
