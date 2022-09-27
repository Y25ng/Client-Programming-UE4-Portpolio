// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "MyProjectile.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "MyBot.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FBotStat : public FTableRowBase // 몬스터 정보 구조체
{
	GENERATED_BODY()
public:
	FBotStat()
	{
		BotMaxHP = 100.f;
		BotLevel = 1;
		BotAttack = 10;
		BotDropExp = 10.f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BotMaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BotLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BotAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BotDropExp;
};

UCLASS()
class MYPROJECT2_API AMyBot : public ABasicCharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AMyBot();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override; // 무기를 캐릭터에 붙여줄 함수
	virtual int melee_attack_Implementation(); // 적의 AI Controller가 사용할 공격 함수 // CombatInterface의 함수를 재정의
	void ThrowBomb(); // 폭탄을 던지는 행동을 수행하는 함수 -> AnimNotifyState에서 지정한 지점에서 호출

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior; // 적의 비헤이비어 트리

	UAnimMontage* get_montage(); // 적의 공격 Anim Montage를 반환

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyBotName; // 적 종류

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class AMyProjectile> MyBomb; // 폭탄 던지는 적의 폭탄


	////////////* 몬스터 데이터 관련 */////////////

	void SetBotStat(int32 NewLevel);
	UDataTable* BotStatTable;
	FBotStat* BotCurrentStat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		TMap<FString, class USoundCue*> BotSoundMap; // 봇 효과음 맵

	void PlaySound(FString SoundName); // 효과음 재생 함수

private:

	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus(); // AI 구현에 따른 자극을 주는 함수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* Attack_Anim; // 적의 공격 Anim Montage
};
