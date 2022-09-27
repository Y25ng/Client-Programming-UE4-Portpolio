// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "BasicCharacter.h"

#include "MyItem.generated.h"


UCLASS()
class MYPROJECT2_API AMyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemCnt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemIcon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
