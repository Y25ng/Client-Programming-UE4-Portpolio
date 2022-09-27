// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBot.h"
#include "MyProjectile.h"
#include "MyBoss.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FBossStat : public FTableRowBase // ���� ���� ����ü
{
	GENERATED_BODY()
public:
	FBossStat()
	{
		BossMaxHP = 10000.f;
		BossLevel = 7;
		BossAttack = 80.f;
		BossDropExp = 80.f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BossMaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BossLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BossAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BossDropExp;
};

UCLASS()
class MYPROJECT2_API AMyBoss : public AMyBot
{
	GENERATED_BODY()

public:
	AMyBoss();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Skill(); // ���� �ñر� �ִϸ��̼� ����
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Skill_Anim; // �ñر� AnimMontage ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* Skill_FX; // �ñر� ���� �� ����� Particle ȿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class AMyProjectile> BossBomb; // �ñر⿡ ���� �߻�ü
	void Skill_Projectile_Create(); // �ñر� �ߵ� �� ���� �߻�ü�� ���� �� �߻�

	void SetBossStat(int32 NewLevel);
	UDataTable* BossStatTable;
	FBossStat* BossCurrentStat;


	bool GetbDuringSkill(); // �ñر� �ִϸ��̼� ������������ ���� ���� ��ȯ
	void SetbDuringSkill(bool Value); // �ñر� �ִϸ��̼� ������������ ���� ���� �Ҵ�
	bool GetbPossibleSkill(); // �ñر� ������ ���������� ���� ���� ��ȯ

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillCoolTime; // �ñر� ��Ÿ��

private:

	bool bDuringSkill; // �ñر� �ִϸ��̼� ������������ ���� ����
	bool bPossibleSkill; // �ñر� �ִϸ��̼� ���� ���������� ���� ����
	float WaitTime; // �ñر⸦ ��ٸ��� �ð�
	
};
