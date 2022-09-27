// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MyProject2GameMode.h"
#include "MyBasicCharacter.h"

#include "Gateway.generated.h"

UCLASS()
class MYPROJECT2_API AGateway : public AActor
{
	GENERATED_BODY()
	
public:	
	AGateway();

protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	// AMyBasicCharacter* MyPlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* mStaticMesh;

	/*
	UPROPERTY(EditAnywhere, Category = "MyGateNum")
		int RandomGateNum;

	UPROPERTY(EditAnywhere, Category = "MyGateNum")
		bool isStageClear;


	FString tempStr;
	int32 tempMapLevel;
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsShowLevelSelect;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	void OpenLevelSelect(AMyBasicCharacter* player);
	void CloseLevelSelect();

private:

	TSubclassOf<class UUserWidget>uiLevelSelectBPClass;
	UUserWidget* uiLevelSelectWidget;
};

