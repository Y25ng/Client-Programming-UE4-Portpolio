// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBasicCharacter.h"
#include "MyBoss.h"
#include "SpawnPoint_Boss.generated.h"

UCLASS()
class MYPROJECT2_API ASpawnPoint_Boss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint_Boss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() // ���� ������ ĳ���Ͱ� ���� ������ �ν��ϸ� ȣ��
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "MyBoss")
		UStaticMeshComponent* mStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere; // �������� �浹ü

	UPROPERTY(EditAnywhere, Category = "MyBoss")
		TSubclassOf<AMyBoss>WhatToSpawn; // ������ų ���� Ÿ��

	UPROPERTY(EditAnywhere, Category = "MyBoss")
		TArray<TSubclassOf<class AMyBoss>>myBoss; // ������ų ����

	void PlayerStop(AMyBoss* Boss); // ������ ������ ��� ������ ���� �ִϸ��̼� ���� �÷��̾ ���߰� ���� �Լ�

private:

	float currentTime;
	float StartAnimTime;

	bool bSpawn; // �� ������ �������� ����
	bool bSpawnComplete; // �� ������ �Ϸ�Ǿ������� ���� ����

	AMyBasicCharacter* Player;

};
