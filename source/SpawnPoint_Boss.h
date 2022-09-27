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

	UFUNCTION() // 지정 공간에 캐릭터가 들어가는 순간을 인식하면 호출
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "MyBoss")
		UStaticMeshComponent* mStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere; // 지정공간 충돌체

	UPROPERTY(EditAnywhere, Category = "MyBoss")
		TSubclassOf<AMyBoss>WhatToSpawn; // 스폰시킬 보스 타입

	UPROPERTY(EditAnywhere, Category = "MyBoss")
		TArray<TSubclassOf<class AMyBoss>>myBoss; // 스폰시킬 보스

	void PlayerStop(AMyBoss* Boss); // 보스가 스폰될 경우 보스의 시작 애니메이션 동안 플레이어를 멈추게 해줄 함수

private:

	float currentTime;
	float StartAnimTime;

	bool bSpawn; // 봇 스폰이 가능한지 여부
	bool bSpawnComplete; // 봇 스폰이 완료되었는지에 대한 여부

	AMyBasicCharacter* Player;

};
