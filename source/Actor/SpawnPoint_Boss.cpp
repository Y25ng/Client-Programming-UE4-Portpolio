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

	bSpawn = false; // 스폰이 가능한지에 대한 여부
	bSpawnComplete = false; // 디폴트 상태 : 지정 봇이 스폰 안된 상태
	currentTime = 0.0f;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPointCom"));
	CollisionSphere->InitSphereRadius(1000.0f);
	RootComponent = CollisionSphere;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint_Boss::OnOverlapBegin); // 지정 공간에 들어갈 시 관련 함수 호출
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

	if (bSpawn && !bSpawnComplete) // 봇이 스폰이 됐다면
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

			if (myNewBoss) // 스폰 몬스터중 보스가 있는지에 대한 여부
			{
				AMyBoss* tempBoss = Cast<AMyBoss>(myNewBoss);
				PlayerStop(tempBoss); // 보스의 시작 Anim 동안 플레이어를 멈춰줌				
			}
		} // 인덱스 내 다음 봇을 스폰


		bSpawnComplete = true;
	}

}

void ASpawnPoint_Boss::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // 지정 공간에 들어간 엑터가 플레이어 캐릭터라면
	{
		Player = Cast<AMyBasicCharacter>(OtherActor); // 플레이어 할당

		if (!bSpawn)
		{
			bSpawn = true; // 봇 스폰이 가능한 상태로 할당
			SetActorTickEnabled(true);
		}
	}
}

void ASpawnPoint_Boss::PlayerStop(AMyBoss* Boss) // 보스의 시작 애니메이션 동안 플레이어를 멈춰줄 함수
{
	Player->SetbIsStarting(true); // 캐릭터가 움직이지 못하게 할당
	float StartingTime;

	if (Boss->GetLevelStart_Anim())
	{
		StartingTime = Boss->GetLevelStart_Anim()->GetPlayLength(); // 보스의 시작 Anim 길이
		FTimerHandle TH_StartingAnim;
		GetWorldTimerManager().SetTimer(TH_StartingAnim, Player, &AMyBasicCharacter::StartAnimEnd, StartingTime, false); // 시작 Anim이 끝났음을 해당 변수에 할당해줌
	}
}
