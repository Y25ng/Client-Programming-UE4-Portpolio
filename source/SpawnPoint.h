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

	UFUNCTION() // ���� ������ ĳ���Ͱ� ���� ������ �ν��ϸ� ȣ��
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "MyBot")
		UStaticMeshComponent* mStaticMesh; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere; // �������� �浹ü

	UPROPERTY(EditAnywhere, Category = "MyBot")
		TSubclassOf<AMyBot>WhatToSpawn; // ������ų �� Ÿ��

	UPROPERTY(EditAnywhere, Category = "MyBot")
		TArray<TSubclassOf<class AMyBot>>myBot; // ������ų ��

private:

	float currentTime;
	float StartAnimTime;

	bool bSpawn; // �� ������ �������� ����
	bool bSpawnComplete; // �� ������ �Ϸ�Ǿ������� ���� ����
};
