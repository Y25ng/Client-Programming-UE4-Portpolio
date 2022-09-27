// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoss.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyBoss::AMyBoss()
{
	/* 보스의 스탯을 연동하는 데이터 테이블 */
	BossStatTable = CreateDefaultSubobject<UDataTable>(TEXT("BossStatTable"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyBossStat_Obj(TEXT("/Game/Data/MyBossStat_DataTable"));
	if (MyBossStat_Obj.Succeeded())
	{
		BossStatTable = MyBossStat_Obj.Object;
	}
	
	bDuringSkill = false; // 궁극기 애니메이션 실행중인지에 대한 여부
	bPossibleSkill = false; // 궁극기 실행 가능한지에 대한 여부
	SkillCoolTime = 20.f; // 궁극기 쿨타임
	WaitTime = 0.0f; // 궁극기를 기다리는 시간
}

void AMyBoss::BeginPlay()
{
	Super::BeginPlay();

	SetBossStat(MyLevel); // 보스의 스텟 초기화
	
}

void AMyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WaitTime += DeltaTime;

	if (WaitTime >= SkillCoolTime)
	{
		if (bPossibleSkill == false)
		{
			bPossibleSkill = true;
			WaitTime = 0.0f;
		}
	}
}

void AMyBoss::SetBossStat(int32 NewLevel) // 보스의 스텟 초기화
{
	BossCurrentStat = BossStatTable->FindRow<FBossStat>(*FString::FromInt(NewLevel), TEXT(""));

	if (BossCurrentStat != nullptr)
	{
		AttackPower = BossCurrentStat->BossAttack; // 공격력

		MyMaxHealth = BossCurrentStat->BossMaxHP; //1000.0f; // HP 최댓값 
		MyHealth = MyMaxHealth; // HP 초기값 할당

		DropEXP = BossCurrentStat->BossDropExp; // 10000.0f; // 봇이 죽을 시 플레이어가 얻게 될 경험치
	}
}

void AMyBoss::Skill() // 보스 궁극기 
{
	if (Skill_Anim)
	{
		bDuringSkill = true; // 궁극기 애니메이션이 실행중임을 할당
		PlaySound("BossSkillReady"); // 보스 궁극기 준비 효과음 재생
		PlayAnimMontage(Skill_Anim); // 보스 궁극기 애니메이션 재생
		bPossibleSkill = false; // 궁극기를 불가능한 상태로 할당
	}
}

void AMyBoss::Skill_Projectile_Create() // 보스 궁극기 발사체 생성
{
	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(0.0f, 0.0f, 0.0f));
	UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		float temp = 0;

		for (int32 i = 0; i < 20; i++) // 45도 간격으로 모든 방향으로 발사체를 발사
		{
			temp = 18.f * i;

			FRotator TempSpawnRotation = SpawnRotation + FRotator(0.f, temp, 0.0f);
			AMyProjectile* SkillProjectile = World->SpawnActor<AMyProjectile>(BossBomb, SpawnLocation, TempSpawnRotation);

			if(SkillProjectile)
				SkillProjectile->ProjectileDamage = AttackPower * 3;
		}
	}
}

bool AMyBoss::GetbDuringSkill()
{
	return bDuringSkill;
}

void AMyBoss::SetbDuringSkill(bool Value)
{
	bDuringSkill = Value;
}

bool AMyBoss::GetbPossibleSkill()
{
	return bPossibleSkill;
}