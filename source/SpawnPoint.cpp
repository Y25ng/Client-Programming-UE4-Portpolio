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

	bSpawn = false; // ������ ���������� ���� ����
	bSpawnComplete = false; // ����Ʈ ���� : ���� ���� ���� �ȵ� ����
	currentTime = 0.0f;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPointCom"));
	CollisionSphere->InitSphereRadius(1000.0f);
	RootComponent = CollisionSphere;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint::OnOverlapBegin); // ���� ������ �� �� ���� �Լ� ȣ��
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// DrawDebugSphere(GetWorld(), GetActorLocation(), 1000.0f, 50, FColor::Green, true, -1, 0, 2); // ���� ������ �ð������� ������
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpawn && !bSpawnComplete) // ���� ������ �ƴٸ�
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
		} // �ε��� �� ���� ���� ����

		bSpawnComplete = true;
	}
}

void ASpawnPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // ���� ������ �� ���Ͱ� �÷��̾� ĳ���Ͷ��
	{
		if (!bSpawn)
		{
			bSpawn = true; // �� ������ ������ ���·� �Ҵ�
			SetActorTickEnabled(true);
		}
	}
}



