// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoss.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyBoss::AMyBoss()
{
	/* ������ ������ �����ϴ� ������ ���̺� */
	BossStatTable = CreateDefaultSubobject<UDataTable>(TEXT("BossStatTable"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyBossStat_Obj(TEXT("/Game/Data/MyBossStat_DataTable"));
	if (MyBossStat_Obj.Succeeded())
	{
		BossStatTable = MyBossStat_Obj.Object;
	}
	
	bDuringSkill = false; // �ñر� �ִϸ��̼� ������������ ���� ����
	bPossibleSkill = false; // �ñر� ���� ���������� ���� ����
	SkillCoolTime = 20.f; // �ñر� ��Ÿ��
	WaitTime = 0.0f; // �ñر⸦ ��ٸ��� �ð�
}

void AMyBoss::BeginPlay()
{
	Super::BeginPlay();

	SetBossStat(MyLevel); // ������ ���� �ʱ�ȭ
	
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

void AMyBoss::SetBossStat(int32 NewLevel) // ������ ���� �ʱ�ȭ
{
	BossCurrentStat = BossStatTable->FindRow<FBossStat>(*FString::FromInt(NewLevel), TEXT(""));

	if (BossCurrentStat != nullptr)
	{
		AttackPower = BossCurrentStat->BossAttack; // ���ݷ�

		MyMaxHealth = BossCurrentStat->BossMaxHP; //1000.0f; // HP �ִ� 
		MyHealth = MyMaxHealth; // HP �ʱⰪ �Ҵ�

		DropEXP = BossCurrentStat->BossDropExp; // 10000.0f; // ���� ���� �� �÷��̾ ��� �� ����ġ
	}
}

void AMyBoss::Skill() // ���� �ñر� 
{
	if (Skill_Anim)
	{
		bDuringSkill = true; // �ñر� �ִϸ��̼��� ���������� �Ҵ�
		PlaySound("BossSkillReady"); // ���� �ñر� �غ� ȿ���� ���
		PlayAnimMontage(Skill_Anim); // ���� �ñر� �ִϸ��̼� ���
		bPossibleSkill = false; // �ñر⸦ �Ұ����� ���·� �Ҵ�
	}
}

void AMyBoss::Skill_Projectile_Create() // ���� �ñر� �߻�ü ����
{
	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(0.0f, 0.0f, 0.0f));
	UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		float temp = 0;

		for (int32 i = 0; i < 20; i++) // 45�� �������� ��� �������� �߻�ü�� �߻�
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