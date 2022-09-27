// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Engine.h"
#include "BasicCharacter.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"
#include "MyBoss.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	bSpawn = false; // 스폰이 가능한지에 대한 여부
	bSpawnComplete = false; // 디폴트 상태 : 지정 봇이 스폰 안된 상태
	currentTime = 0.0f;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPointCom"));
	CollisionSphere->InitSphereRadius(1000.0f);
	RootComponent = CollisionSphere;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint::OnOverlapBegin); // 지정 공간에 들어갈 시 관련 함수 호출
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// DrawDebugSphere(GetWorld(), GetActorLocation(), 1000.0f, 50, FColor::Green, true, -1, 0, 2); // 지정 공간을 시각적으로 보여줌
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpawn && !bSpawnComplete) // 봇이 스폰이 됐다면
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();

		UWorld* WRLD = GetWorld();

		FVector location = GetActorLocation();
		FRotator rotation = GetActorRotation();

		for (int i = 0; i < myBot.Num(); ++i)
		{
			AMyBot* const myNewBot = GetWorld()->SpawnActor<AMyBot>(myBot[i], location, rotation);
		} // 인덱스 내 다음 봇을 스폰

		bSpawnComplete = true;
	}
}

void ASpawnPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // 지정 공간에 들어간 엑터가 플레이어 캐릭터라면
	{
		if (!bSpawn)
		{
			bSpawn = true; // 봇 스폰이 가능한 상태로 할당
			SetActorTickEnabled(true);
		}
	}
}



