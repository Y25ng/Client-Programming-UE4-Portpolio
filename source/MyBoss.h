// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBot.h"
#include "MyProjectile.h"
#include "MyBoss.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FBossStat : public FTableRowBase // 몬스터 정보 구조체
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

	void Skill(); // 보스 궁극기 애니메이션 실행
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Skill_Anim; // 궁극기 AnimMontage 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* Skill_FX; // 궁극기 실행 시 출력할 Particle 효과
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class AMyProjectile> BossBomb; // 궁극기에 사용될 발사체
	void Skill_Projectile_Create(); // 궁극기 발동 시 나갈 발사체를 생성 후 발사

	void SetBossStat(int32 NewLevel);
	UDataTable* BossStatTable;
	FBossStat* BossCurrentStat;


	bool GetbDuringSkill(); // 궁극기 애니메이션 실행중인지에 대한 여부 반환
	void SetbDuringSkill(bool Value); // 궁극기 애니메이션 실행중인지에 대한 여부 할당
	bool GetbPossibleSkill(); // 궁극기 실행이 가능한지에 대한 여부 반환

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillCoolTime; // 궁극기 쿨타임

private:

	bool bDuringSkill; // 궁극기 애니메이션 실행중인지에 대한 여부
	bool bPossibleSkill; // 궁극기 애니메이션 실행 가능한지에 대한 여부
	float WaitTime; // 궁극기를 기다리는 시간
	
};
