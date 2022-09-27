// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "Engine/DataTable.h" // 데이터테이블 사용 라이브러리
#include "MyWeapon.h" // 무기 클래스
#include "CameraShakeObstacle.h"
#include "SkillAttack1_Projectile.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "CombatInterface.h"
#include "MyCharacterStatComponent.h"

#include "Camera/CameraShake.h"

#include "Animation/AnimMontage.h"
#include "MyBasicCharacter.generated.h"

/**
 * 
 */

/*
USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	FCharacterInfo()
	{
		CharacterHP = 1000.f;
		CharacterMP = 500.f;
		CharacterLevel = 1;
		CharacterName = FText::FromString("Name");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CharacterMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CharacterLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 PlayerGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText CharacterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CharacterThumbnail;
};
*/

/*
USTRUCT(BlueprintType) // 구조체 블루프린트 연동
struct FItem : public FTableRowBase // 캐릭터 스킬 정보
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
*/

UCLASS()
class MYPROJECT2_API AMyBasicCharacter : public ABasicCharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AMyBasicCharacter(); // 생성자

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override; // 무기를 캐릭터에 붙여줄 함수


	//////////////////////////* 카메라 관련 *///////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	class USpringArmComponent* CameraBoom; // 카메라 지지대

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	class UCameraComponent* FollowCamera; // 카메라

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		TSubclassOf<UMatineeCameraShake> CameraShakeClass; // 카메라 쉐이크
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		TSubclassOf<UMatineeCameraShake> CameraShakeClass2; // 카메라 쉐이크


	//////////////////////////////////////////////////////////////////
	///////////////////////* 공격 함수 *//////////////////////////////
	/////////////////////////////////////////////////////////////////

	int32 GetSkillIndex();
	void CoolTimeEnd(); // 쿨타임 완료 여부 변수에 true를 할당

	//////////////////////* 스킬 1 *////////////////////////////////

	void SkillAttack1(); // 스킬1 실행 함수

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* SkillAttack1_Anim; // 스킬1 AnimMontage 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack1_FX; // 스킬1 실행 시 출력할 Particle 효과
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class ASkillAttack1_Projectile> Skill1_Projectile; // 스킬1 발동 시 나갈 발사체
	void SkillAttack1_Projectile_Create(); // 스킬1 발동 시 나갈 발사체를 생성 후 발사

	//////////////////////* 스킬 2 *////////////////////////////////

	void SkillAttack2(); // 스킬2 실행 함수

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* SkillAttack2_Anim; // 스킬2 AnimMontage 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack2_FX; // 스킬2 실행 시 출력할 Particle 효과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack2_Explode_FX; // 스킬2 실행 시 출력할 폭발 Particle 효과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack2_WarmUp_FX; // 스킬2 준비 동작 시 출력할 Particle 효과
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class ASkillAttack1_Projectile> Skill2_Projectile; // 스킬2 발동 시 나갈 발사체
	void SkillAttack2_Projectile_Create(); // 스킬2 발동 시 나갈 발사체를 생성 후 발사
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		bool bSkill2Possible; // 스킬2를 실행할 수 있는 상태인지에 대한 여부 -> 쿨타임이 끝났는지


	virtual void OnChangeWeapon(); // 상속 받아 재정의 할 무기 교체 함수
	virtual void LevelUpUpdate(); // 상속 받아 재정의 할 레벨 업 스탯 업데이트 함수

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		TArray<class USoundCue*> BGM_Sound_Arr; // 맵 별 배경음악

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		TMap<FString, class USoundCue*> SoundMap; // 효과음

	void PlaySound(FString SoundName); // 효과음 재생 함수

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // 입력 키바인딩
	void MoveForward(float value); // 앞으로 이동 함수
	void MoveRight(float value); // 오른쪽으로 이동 함수
	void MyJump(); // 점프 함수
	void BoosterOnOff(); // 부스터 ON/OFF 함수

private:

	/////////////////////////////* 부스터 관련 *///////////////////////////////////

	bool bIsBoosterOn; // 부스터 ON/OFF 여부에 대한 변수
	int32 SkillIndex; // 스킬1 실행 여부 함수
	float BoosterGage; // 부스터 게이지 수치
	float MaxBoosterGage; // 부스터 게이지 최대 수치
	float BoosterGageNum; // 부스터 게이지 / 최대 부스터 게이지

	class UWidgetComponent* BoosterGage_Widget_Component; // 캐릭터 머리위 부스터 게이지 위젯
	TSubclassOf<class UUserWidget> BoosterGage_Widget_Class;

};
