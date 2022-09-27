// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"// box 충돌체를 위한 라이브러리
#include "MyDoor.generated.h"

UCLASS()
class MYPROJECT2_API AMyDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//UStaticMeshComponent* DoorMesh; // 문 Mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionBox; // 충돌체

	UPROPERTY(EditAnywhere)
		float CloseTime; // 문이 닫히는데에 걸리는 시간

	float DoorDeltaTime; // 문을 열고 닫는데에 사용할 시간 단위

	bool bOpen; // 문이 열려있는지에 대한 여부를 할당
	bool bOnlyBoss; // 보스 빼고 몬스터들을 모두 죽였는지에 대한 여부를 할당 

	FTimerHandle DoorTimerHandle; // 문 열고 닫는 시간을 체크할 때 사용할 타이머

	FRotator OriginRotation; // 문이 닫힌 상태의 회전값

	void Open(); // 문 열기 함수

	float StartAngle;
	float EndAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundCue* DoorOpen_Sound; // 게이트 오픈 사운드
};
