// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDoor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyBasicCharacter.h"
#include "Engine.h"

// Sets default values
AMyDoor::AMyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(400.f, 20.f, 400.f));
	RootComponent = CollisionBox;

	CloseTime = 3.f;
	StartAngle = 0.0f;
	EndAngle = 180.0f;

}

// Called when the game starts or when spawned
void AMyDoor::BeginPlay()
{
	Super::BeginPlay();

	OriginRotation = GetActorRotation();
	bOpen = false;
}

// Called every frame
void AMyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorDeltaTime += DeltaTime;
}

void AMyDoor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (bOpen == true)
		return;

	AMyBasicCharacter* Player = Cast<AMyBasicCharacter>(OtherActor);

	if (Player != nullptr && Player->GetbAllMonsterDie() == true)
	{
		// 게이트 오픈 소리 출력
		if (DoorOpen_Sound != nullptr)
			UGameplayStatics::SpawnSoundAttached(DoorOpen_Sound, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);

		GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &AMyDoor::Open, 0.03f, true);
	}
}

void AMyDoor::Open()
{
	if (bOpen == false)
	{
		bOpen = true;
		DoorDeltaTime = 0.0f;
	}

	FRotator rotation = GetActorRotation();
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(StartAngle, EndAngle, DoorDeltaTime), 0.0f);
	SetActorRotation(rotation);

	if (DoorDeltaTime > 1.0f)
	{
		GetWorldTimerManager().ClearTimer(DoorTimerHandle);
	}
}

