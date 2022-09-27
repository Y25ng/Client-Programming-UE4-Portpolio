// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyWeapon.h"
#include "Engine/DataTable.h" // 데이터테이블 사용 라이브러리
#include "MySaveGame.h"

#include "BasicCharacter.generated.h"

USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FCharacterStat : public FTableRowBase // 캐릭터 스텟 정보
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

USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FCharacterSkill : public FTableRowBase // 캐릭터 스킬 정보
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

USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FItem : public FTableRowBase // 캐릭터 소유 아이템 정보
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

USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FDungeonClearReward : public FTableRowBase // 던전별 정보
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // 키 바인딩 함수


	////////////////////////* 프로퍼티 *///////////////////////////////////

	bool GetbAllMonsterDie(); // 현 던전에서 모든 몬스터가 죽었는지에 대한 여부

	FString GetNickName(); // 캐릭터 닉네임 반환
	void SetNickName(FString Value); // 캐릭터 닉네임 할당

	FName GetMyCharacterName(); // Pawn 종류 반환 함수
	FName GetWeaponAttachPoint() const; // 무기를 장착할 소켓 이름 반환

	AMyWeapon* GetCurrentWeapon(); // 현재 무기 반환

	FString GetSaveSlotName(); // 데이터를 저장할 슬롯 이름 반환

	int32 GetMyGold(); // 골드 반환
	void SetMyGold(int32 Value); // 골드 값 할당

	float Get_Health() const; // 현재 체력 반환
	void Set_Health(float Value); // 현재 체력에 새로운 값 할당
	float Get_MaxHealth() const; // 최대 체력 반환

	float Get_MP() const; // 현재 MP 반환
	void Set_MP(float Value); // 현재 MP에 새로운 값 할당
	float Get_MaxMP(); // 최대 MP 반환

	float Get_Exp() const; // 현재 Exp 반환
	void Set_Exp(float Value); // 현재 Exp 할당

	float Get_AttackPower(); // 공격력 반환

	USkeletalMeshComponent* GetSpecificPawnMesh() const; // 무기를 붙일 캐릭터 메쉬 반환

	TArray<class AMyWeapon*> GetWeaponInventory(); // 소유중인 무기 배열

	void SetbIsDuringAttack(bool Value); // 공격중인지 여부를 할당
	bool GetbIsDuringAttack(); // 공격중인지 여부를 반환

	void SetComboAttack_Num(int32 Value);  // 콤보 카운트를 할당S
	int32 GetComboAttack_Num(); // 콤보 카운트를 반환
	bool GetbFinalAttack(); // 콤보 마지막 공격인지 여부에 대한 반환
	void SetbFinalAttack(bool Value); // 콤보 마지막 공격인지 여부를 할당

	void SetbDamagePossible(bool Value); // 데미지를 입힐 수 있는지를 할당
	bool GetbDamagePossible(); // 데미지를 입힐 수 있는지를 반환
	bool GetbIsStarting(); // 레벨 시작 Anim이 진행중인지를 반환
	void SetbIsStarting(bool Value); // 레벨 시작 Anim이 진행중인지를 할당

	bool GetbIsDuringHitAnim(); // Hit Anim이 진행중인지를 반환
	void SetbIsDuringHitAnim(bool Value); // Hit Anim이 진행중인지를 할당

	bool GetbIsDuringJumpEnd(); // 점프 End가 진행중인지에 대한 여부 반환
	void SetbIsDuringJumpEnd(bool Value); // 점프 End가 진행중인지에 대한 여부 할당

	void SetbJumpAttack(bool Value); // 공중 공격을 수행했는지에 대한 여부 할당

	int32 GetDungeonLevel(); // 캐릭터가 속한 던전 레벨 반환 함수

	void SetDungeonLevel(int32 Value); // 캐릭터가 속한 던전 레벨 할당 함수

	UAnimMontage* GetLevelStart_Anim(); // 레벨 시작 Anim Montage 반환 함수


	// TArray<UAnimMontage*> GetAttack_Anim_Arr();

	////////////////////////* 공격 관련 함수 *///////////////////////////////////


	void Attack(); // 공격 함수
	void AttackEnd(); // 공격 종료 함수


	////////////////////////* 시작 Anim 관련 함수 *///////////////////////////////////


	void StartAnim(); // 시작 애니메이션 실행
	void StartAnimEnd(); // 시작 애니메이션 종료


	////////////////////////* 무기 관련 함수 *///////////////////////////////////


	void EquipWeapon(class AMyWeapon* Weapon); // 무기 장착을 위한 함수
	void SetCurrentWeapon(class AMyWeapon* NewWeapon, class AMyWeapon* LastWeapon); // 현재 무기를 설정할 함수
	void AddWeapon(AMyWeapon* Weapon); // 무기 인벤토리에 추가
	void OnChangeWeapon(); // 무기 교체 함수
	void SpawndefaultInventory(); // 인벤토리에 있는 무기를 불러와줄 함수


	////////////////////////* 데미지 관련 함수 *///////////////////////////////////


	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser); // 데미지를 받을 때 호출
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override; // 데미지를 반환
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser); // 죽음 함수
	void DeathAnimEnd(); // 죽음 이후 캐릭터를 지워주는 함수


	////////////////////////* 데이터 테이블 연동 관련 *///////////////////////////////////

	void SaveCharacterStat(); // 캐릭터 스텟 저장 
	void SetCharacterStat(); // 데이터 테이블 연동을 통한 캐릭터 스텟 세팅
	void LevelUpUpdate(); // 레벨업 스텟 업데이트

	UDataTable* CharacterStatTable; // 캐릭터 스텟 데이터 테이블
	FCharacterStat* CharacterCurrentStat; // 캐릭터 스텟 데이터 테이블 기반 구조체 포인터 객체

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* CharacterSkillTable; // 캐릭터 스킬 데이터 테이블
	FCharacterSkill* CharacterCurrentSkill; // 캐릭터 스킬 데이터 테이블 기반 구조체 포인터 객체

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* MyItemDataTable; // 캐릭터 아이템 데이터 테이블
	FItem* MyCurrentItem; // 캐릭터 아이템 데이터 테이블 기반 구조체 포인터 객체

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* DungeonDataTable; // 던전 데이터 테이블
	FDungeonClearReward* CurrentDungeon; //  데이터 테이블 기반 구조체 포인터 객체

protected:
	////////////////////////* 플래그 변수 *///////////////////////////////////


	bool bIsDuringAttack; // 공격이 가능한지에 대한 여부
	bool bIsStarting; // 시작 애니메이션 수행중
	bool bComboPossible; // 콤보 가능한지에 대한 여부
	bool bFinalAttack; // 콤보 마지막인지에 대한 여부
	bool bDamagePossible; // 데미지를 입힐 수 있는지에 대한 여부
	bool bIsDuringHitAnim; // Hit Anim이 실행중인지에 대한 여부
	bool bIsDuringJumpEnd; // Jump End Anim이 실행중인지 여부
	bool bJumpAttack; // 점프 공격중인지에 대한 여부


	////////////////////////* Anim_Montage *///////////////////////////////////


	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* LevelStart_Anim; // 레벨 시작 때의 AnimMontage 저장
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* BeHit_Anim; // 공격 당할 때의 AnimMontage 저장
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Death_Anim; // 죽을 때의 AnimMontage 저장

	// UPROPERTY(EditDefaultsOnly, Category = Pawn)
		// TArray<UAnimMontage*> Attack_Anim_Arr; // 공격 AnimMontage 저장


	////////////////////////* 기타 변수 *///////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyState)
		int32 DungeonLevel; // 던전 레벨

	int32 ComboAttack_Num; // 콤보 수
	FString SaveSlotName; // 캐릭터 스탯 저장 슬롯 이름
	
	TArray<int32> DungeonMonsterCnt; // 단계별 죽여야하는 몬스터 수
	int32 PlayerKillCnt; // 플레이어가 죽인 몬스터 수
	bool bAllMonsterDie; // 모든 몬스터가 죽었는지에 대한 여부

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		int MyGold; // 캐릭터 Gold

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float AttackPower; // 공격력

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString NickName; // 캐릭터 닉네임

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyCharacterName; // Pawn 종류 구분
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		FName WeaponAttachPoint; // 소켓 이름

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyHealth; // 캐릭터 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMaxHealth; // 캐릭터 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMP;  // 캐릭터 MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMaxMP; // 캐릭터 최대 MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyEXP; // 캐릭터 경험치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMaxEXP; // 캐릭터 최대 경험치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float DropEXP; // 봇이 죽을 경우 캐릭터가 얻게 될 경험치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		int32 MyLevel; // 캐릭터 레벨

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyHPNum; // 캐릭터 HP / 캐릭터 최대 HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMPNum; // 캐릭터 MP / 캐릭터 최대 MP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyEXPNum; // 캐릭터 EXP / 캐릭터 최대 EXP

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString MyHPNum_String; // Widget에 출력할 HP ( 캐릭터 HP / 캐릭터 최대 HP )
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString MyMPNum_String; // Widget에 출력할 MP ( 캐릭터 MP / 캐릭터 최대 MP )
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FString MyEXPNum_String; // Widget에 출력할 EXP ( 캐릭터 EXP / 캐릭터 최대 EXP )

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
		TArray<class AMyWeapon*> Inventory; // 무기 목록
	class AMyWeapon* CurrentWeapon; // 현재 무기

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class AMyWeapon>>DefaultInventoryClasses; // 무기 종류

	class UWidgetComponent* Widget_Component; // 캐릭터 머리위의 체력바

	// 던전 보상 Widget 관련
	TSubclassOf<class UUserWidget>uiDungeonRewardBPClass; 
	UUserWidget* uiDungeonRewardWidget;

	// 플레이어 닉네임 입력 Widget
	TSubclassOf<class UUserWidget>uiCharacterNameBPClass;
	UUserWidget* uiCharacterNameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* LevelUpFX; // 플레이어가 레벨업 할 때 출력할 Particle 효과
};