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

USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FBotStat : public FTableRowBase // ���� ���� ����ü
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

	virtual void PostInitializeComponents() override; // ���⸦ ĳ���Ϳ� �ٿ��� �Լ�
	virtual int melee_attack_Implementation(); // ���� AI Controller�� ����� ���� �Լ� // CombatInterface�� �Լ��� ������
	void ThrowBomb(); // ��ź�� ������ �ൿ�� �����ϴ� �Լ� -> AnimNotifyState���� ������ �������� ȣ��

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior; // ���� �����̺�� Ʈ��

	UAnimMontage* get_montage(); // ���� ���� Anim Montage�� ��ȯ

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyBotName; // �� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class AMyProjectile> MyBomb; // ��ź ������ ���� ��ź


	////////////* ���� ������ ���� */////////////

	void SetBotStat(int32 NewLevel);
	UDataTable* BotStatTable;
	FBotStat* BotCurrentStat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		TMap<FString, class USoundCue*> BotSoundMap; // �� ȿ���� ��

	void PlaySound(FString SoundName); // ȿ���� ��� �Լ�

private:

	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus(); // AI ������ ���� �ڱ��� �ִ� �Լ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* Attack_Anim; // ���� ���� Anim Montage
};
