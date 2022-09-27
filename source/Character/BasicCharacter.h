// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyWeapon.h"
#include "Engine/DataTable.h" // ���������̺� ��� ���̺귯��
#include "MySaveGame.h"

#include "BasicCharacter.generated.h"

USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FCharacterStat : public FTableRowBase // ĳ���� ���� ����
{
	GENERATED_BODY()
public:
	FCharacterStat()
	{
		MaxHP = 1000.f;
		MaxMP = 500.f;
		Level = 1;
		Attack = 10;
		NextExp = 10000.f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NextExp;
};

USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FCharacterSkill : public FTableRowBase // ĳ���� ��ų ����
{
	GENERATED_BODY()
public:
	FCharacterSkill()
	{
		ConsumeMP = 50.f;
		ActivationLevel = 1;
		SkillPower = 20.f;
		CoolTime = 5.f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ConsumeMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ActivationLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SkillPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CoolTime;
};

USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FItem : public FTableRowBase // ĳ���� ���� ������ ����
{
	GENERATED_BODY()
public:
	FItem()
	{
		ItemNumber = 0;
		ItemCnt = 0;
		ItemName = "";
		ItemIcon = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemCnt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* ItemIcon;
};

USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FDungeonClearReward : public FTableRowBase // ������ ����
{
	GENERATED_BODY()
public:
	FDungeonClearReward()
	{
		DungeonLevel = 1;
		bDungeonClear = false;
		RewardGold = 0;
		RewardExp = 0;
		DungeonImage = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DungeonLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDungeonClear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RewardGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RewardExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DungeonImage;

};

UCLASS()
class MYPROJECT2_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABasicCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Ű ���ε� �Լ�


	////////////////////////* ������Ƽ *///////////////////////////////////

	bool GetbAllMonsterDie(); // �� �������� ��� ���Ͱ� �׾������� ���� ����

	FString GetNickName(); // ĳ���� �г��� ��ȯ
	void SetNickName(FString Value); // ĳ���� �г��� �Ҵ�

	FName GetMyCharacterName(); // Pawn ���� ��ȯ �Լ�
	FName GetWeaponAttachPoint() const; // ���⸦ ������ ���� �̸� ��ȯ

	AMyWeapon* GetCurrentWeapon(); // ���� ���� ��ȯ

	FString GetSaveSlotName(); // �����͸� ������ ���� �̸� ��ȯ

	int32 GetMyGold(); // ��� ��ȯ
	void SetMyGold(int32 Value); // ��� �� �Ҵ�

	float Get_Health() const; // ���� ü�� ��ȯ
	void Set_Health(float Value); // ���� ü�¿� ���ο� �� �Ҵ�
	float Get_MaxHealth() const; // �ִ� ü�� ��ȯ

	float Get_MP() const; // ���� MP ��ȯ
	void Set_MP(float Value); // ���� MP�� ���ο� �� �Ҵ�
	float Get_MaxMP(); // �ִ� MP ��ȯ

	float Get_Exp() const; // ���� Exp ��ȯ
	void Set_Exp(float Value); // ���� Exp �Ҵ�

	float Get_AttackPower(); // ���ݷ� ��ȯ

	USkeletalMeshComponent* GetSpecificPawnMesh() const; // ���⸦ ���� ĳ���� �޽� ��ȯ

	TArray<class AMyWeapon*> GetWeaponInventory(); // �������� ���� �迭

	void SetbIsDuringAttack(bool Value); // ���������� ���θ� �Ҵ�
	bool GetbIsDuringAttack(); // ���������� ���θ� ��ȯ

	void SetComboAttack_Num(int32 Value);  // �޺� ī��Ʈ�� �Ҵ�S
	int32 GetComboAttack_Num(); // �޺� ī��Ʈ�� ��ȯ
	bool GetbFinalAttack(); // �޺� ������ �������� ���ο� ���� ��ȯ
	void SetbFinalAttack(bool Value); // �޺� ������ �������� ���θ� �Ҵ�

	void SetbDamagePossible(bool Value); // �������� ���� �� �ִ����� �Ҵ�
	bool GetbDamagePossible(); // �������� ���� �� �ִ����� ��ȯ
	bool GetbIsStarting(); // ���� ���� Anim�� ������������ ��ȯ
	void SetbIsStarting(bool Value); // ���� ���� Anim�� ������������ �Ҵ�

	bool GetbIsDuringHitAnim(); // Hit Anim�� ������������ ��ȯ
	void SetbIsDuringHitAnim(bool Value); // Hit Anim�� ������������ �Ҵ�

	bool GetbIsDuringJumpEnd(); // ���� End�� ������������ ���� ���� ��ȯ
	void SetbIsDuringJumpEnd(bool Value); // ���� End�� ������������ ���� ���� �Ҵ�

	void SetbJumpAttack(bool Value); // ���� ������ �����ߴ����� ���� ���� �Ҵ�

	int32 GetDungeonLevel(); // ĳ���Ͱ� ���� ���� ���� ��ȯ �Լ�

	void SetDungeonLevel(int32 Value); // ĳ���Ͱ� ���� ���� ���� �Ҵ� �Լ�

	UAnimMontage* GetLevelStart_Anim(); // ���� ���� Anim Montage ��ȯ �Լ�


	// TArray<UAnimMontage*> GetAttack_Anim_Arr();

	////////////////////////* ���� ���� �Լ� *///////////////////////////////////


	void Attack(); // ���� �Լ�
	void AttackEnd(); // ���� ���� �Լ�


	////////////////////////* ���� Anim ���� �Լ� *///////////////////////////////////


	void StartAnim(); // ���� �ִϸ��̼� ����
	void StartAnimEnd(); // ���� �ִϸ��̼� ����


	////////////////////////* ���� ���� �Լ� *///////////////////////////////////


	void EquipWeapon(class AMyWeapon* Weapon); // ���� ������ ���� �Լ�
	void SetCurrentWeapon(class AMyWeapon* NewWeapon, class AMyWeapon* LastWeapon); // ���� ���⸦ ������ �Լ�
	void AddWeapon(AMyWeapon* Weapon); // ���� �κ��丮�� �߰�
	void OnChangeWeapon(); // ���� ��ü �Լ�
	void SpawndefaultInventory(); // �κ��丮�� �ִ� ���⸦ �ҷ����� �Լ�


	////////////////////////* ������ ���� �Լ� *///////////////////////////////////


	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser); // �������� ���� �� ȣ��
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override; // �������� ��ȯ
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser); // ���� �Լ�
	void DeathAnimEnd(); // ���� ���� ĳ���͸� �����ִ� �Լ�


	////////////////////////* ������ ���̺� ���� ���� *///////////////////////////////////

	void SaveCharacterStat(); // ĳ���� ���� ���� 
	void SetCharacterStat(); // ������ ���̺� ������ ���� ĳ���� ���� ����
	void LevelUpUpdate(); // ������ ���� ������Ʈ

	UDataTable* CharacterStatTable; // ĳ���� ���� ������ ���̺�
	FCharacterStat* CharacterCurrentStat; // ĳ���� ���� ������ ���̺� ��� ����ü ������ ��ü

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* CharacterSkillTable; // ĳ���� ��ų ������ ���̺�
	FCharacterSkill* CharacterCurrentSkill; // ĳ���� ��ų ������ ���̺� ��� ����ü ������ ��ü

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* MyItemDataTable; // ĳ���� ������ ������ ���̺�
	FItem* MyCurrentItem; // ĳ���� ������ ������ ���̺� ��� ����ü ������ ��ü

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* DungeonDataTable; // ���� ������ ���̺�
	FDungeonClearReward* CurrentDungeon; //  ������ ���̺� ��� ����ü ������ ��ü

protected:
	////////////////////////* �÷��� ���� *///////////////////////////////////


	bool bIsDuringAttack; // ������ ���������� ���� ����
	bool bIsStarting; // ���� �ִϸ��̼� ������
	bool bComboPossible; // �޺� ���������� ���� ����
	bool bFinalAttack; // �޺� ������������ ���� ����
	bool bDamagePossible; // �������� ���� �� �ִ����� ���� ����
	bool bIsDuringHitAnim; // Hit Anim�� ������������ ���� ����
	bool bIsDuringJumpEnd; // Jump End Anim�� ���������� ����
	bool bJumpAttack; // ���� ������������ ���� ����


	////////////////////////* Anim_Montage *///////////////////////////////////


	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* LevelStart_Anim; // ���� ���� ���� AnimMontage ����
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* BeHit_Anim; // ���� ���� ���� AnimMontage ����
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Death_Anim; // ���� ���� AnimMontage ����

	// UPROPERTY(EditDefaultsOnly, Category = Pawn)
		// TArray<UAnimMontage*> Attack_Anim_Arr; // ���� AnimMontage ����


	////////////////////////* ��Ÿ ���� *///////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyState)
		int32 DungeonLevel; // ���� ����

	int32 ComboAttack_Num; // �޺� ��
	FString SaveSlotName; // ĳ���� ���� ���� ���� �̸�
	
	TArray<int32> DungeonMonsterCnt; // �ܰ躰 �׿����ϴ� ���� ��
	int32 PlayerKillCnt; // �÷��̾ ���� ���� ��
	bool bAllMonsterDie; // ��� ���Ͱ� �׾������� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		int MyGold; // ĳ���� Gold

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float AttackPower; // ���ݷ�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString NickName; // ĳ���� �г���

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyCharacterName; // Pawn ���� ����
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		FName WeaponAttachPoint; // ���� �̸�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyHealth; // ĳ���� ü��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMaxHealth; // ĳ���� �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMP;  // ĳ���� MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMaxMP; // ĳ���� �ִ� MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyEXP; // ĳ���� ����ġ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMaxEXP; // ĳ���� �ִ� ����ġ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float DropEXP; // ���� ���� ��� ĳ���Ͱ� ��� �� ����ġ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		int32 MyLevel; // ĳ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyHPNum; // ĳ���� HP / ĳ���� �ִ� HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMPNum; // ĳ���� MP / ĳ���� �ִ� MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyEXPNum; // ĳ���� EXP / ĳ���� �ִ� EXP

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString MyHPNum_String; // Widget�� ����� HP ( ĳ���� HP / ĳ���� �ִ� HP )
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString MyMPNum_String; // Widget�� ����� MP ( ĳ���� MP / ĳ���� �ִ� MP )
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString MyEXPNum_String; // Widget�� ����� EXP ( ĳ���� EXP / ĳ���� �ִ� EXP )

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
		TArray<class AMyWeapon*> Inventory; // ���� ���
	class AMyWeapon* CurrentWeapon; // ���� ����

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class AMyWeapon>>DefaultInventoryClasses; // ���� ����

	class UWidgetComponent* Widget_Component; // ĳ���� �Ӹ����� ü�¹�

	// ���� ���� Widget ����
	TSubclassOf<class UUserWidget>uiDungeonRewardBPClass; 
	UUserWidget* uiDungeonRewardWidget;

	// �÷��̾� �г��� �Է� Widget
	TSubclassOf<class UUserWidget>uiCharacterNameBPClass;
	UUserWidget* uiCharacterNameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* LevelUpFX; // �÷��̾ ������ �� �� ����� Particle ȿ��
};