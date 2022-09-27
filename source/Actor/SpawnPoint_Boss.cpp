// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint_Boss.h"
#include "Engine.h"
#include "MyBasicCharacter.h"
#include "MyBoss.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ASpawnPoint_Boss::ASpawnPoint_Boss()
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

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint_Boss::OnOverlapBegin); // ���� ������ �� �� ���� �Լ� ȣ��
}

// Called when the game starts or when spawned
void ASpawnPoint_Boss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPoint_Boss::Tick(float DeltaTime)
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

		for (int i = 0; i < myBoss.Num(); ++i)
		{
			AMyBoss* const myNewBoss = GetWorld()->SpawnActor<AMyBoss>(myBoss[i], location, rotation);

			if (myNewBoss) // ���� ������ ������ �ִ����� ���� ����
			{
				AMyBoss* tempBoss = Cast<AMyBoss>(myNewBoss);
				PlayerStop(tempBoss); // ������ ���� Anim ���� �÷��̾ ������				
			}
		} // �ε��� �� ���� ���� ����


		bSpawnComplete = true;
	}

}

void ASpawnPoint_Boss::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // ���� ������ �� ���Ͱ� �÷��̾� ĳ���Ͷ��
	{
		Player = Cast<AMyBasicCharacter>(OtherActor); // �÷��̾� �Ҵ�

		if (!bSpawn)
		{
			bSpawn = true; // �� ������ ������ ���·� �Ҵ�
			SetActorTickEnabled(true);
		}
	}
}

void ASpawnPoint_Boss::PlayerStop(AMyBoss* Boss) // ������ ���� �ִϸ��̼� ���� �÷��̾ ������ �Լ�
{
	Player->SetbIsStarting(true); // ĳ���Ͱ� �������� ���ϰ� �Ҵ�
	float StartingTime;

	if (Boss->GetLevelStart_Anim())
	{
		StartingTime = Boss->GetLevelStart_Anim()->GetPlayLength(); // ������ ���� Anim ����
		FTimerHandle TH_StartingAnim;
		GetWorldTimerManager().SetTimer(TH_StartingAnim, Player, &AMyBasicCharacter::StartAnimEnd, StartingTime, false); // ���� Anim�� �������� �ش� ������ �Ҵ�����
	}
}
