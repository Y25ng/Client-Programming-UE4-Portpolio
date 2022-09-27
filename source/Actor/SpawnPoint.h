// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicCharacter.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"
#include "SpawnPoint.generated.h"

UCLASS()
class MYPROJECT2_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() // 지정 공간에 캐릭터가 들어가는 순간을 인식하면 호출
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "MyBot")
		UStaticMeshComponent* mStaticMesh; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere; // 지정공간 충돌체

	UPROPERTY(EditAnywhere, Category = "MyBot")
		TSubclassOf<AMyBot>WhatToSpawn; // 스폰시킬 봇 타입

	UPROPERTY(EditAnywhere, Category = "MyBot")
		TArray<TSubclassOf<class AMyBot>>myBot; // 스폰시킬 봇

private:

	float currentTime;
	float StartAnimTime;

	bool bSpawn; // 봇 스폰이 가능한지 여부
	bool bSpawnComplete; // 봇 스폰이 완료되었는지에 대한 여부
};
