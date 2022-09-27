// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "Engine/DataTable.h" // ���������̺� ��� ���̺귯��
#include "MyWeapon.h" // ���� Ŭ����
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
USTRUCT(BlueprintType) // ����ü �������Ʈ ����
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
USTRUCT(BlueprintType) // ����ü �������Ʈ ����
struct FItem : public FTableRowBase // ĳ���� ��ų ����
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
	AMyBasicCharacter(); // ������

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override; // ���⸦ ĳ���Ϳ� �ٿ��� �Լ�


	//////////////////////////* ī�޶� ���� *///////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	class USpringArmComponent* CameraBoom; // ī�޶� ������

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	class UCameraComponent* FollowCamera; // ī�޶�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		TSubclassOf<UMatineeCameraShake> CameraShakeClass; // ī�޶� ����ũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		TSubclassOf<UMatineeCameraShake> CameraShakeClass2; // ī�޶� ����ũ


	//////////////////////////////////////////////////////////////////
	///////////////////////* ���� �Լ� *//////////////////////////////
	/////////////////////////////////////////////////////////////////

	int32 GetSkillIndex();
	void CoolTimeEnd(); // ��Ÿ�� �Ϸ� ���� ������ true�� �Ҵ�

	//////////////////////* ��ų 1 *////////////////////////////////

	void SkillAttack1(); // ��ų1 ���� �Լ�

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* SkillAttack1_Anim; // ��ų1 AnimMontage ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack1_FX; // ��ų1 ���� �� ����� Particle ȿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class ASkillAttack1_Projectile> Skill1_Projectile; // ��ų1 �ߵ� �� ���� �߻�ü
	void SkillAttack1_Projectile_Create(); // ��ų1 �ߵ� �� ���� �߻�ü�� ���� �� �߻�

	//////////////////////* ��ų 2 *////////////////////////////////

	void SkillAttack2(); // ��ų2 ���� �Լ�

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* SkillAttack2_Anim; // ��ų2 AnimMontage ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack2_FX; // ��ų2 ���� �� ����� Particle ȿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack2_Explode_FX; // ��ų2 ���� �� ����� ���� Particle ȿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* SkillAttack2_WarmUp_FX; // ��ų2 �غ� ���� �� ����� Particle ȿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class ASkillAttack1_Projectile> Skill2_Projectile; // ��ų2 �ߵ� �� ���� �߻�ü
	void SkillAttack2_Projectile_Create(); // ��ų2 �ߵ� �� ���� �߻�ü�� ���� �� �߻�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		bool bSkill2Possible; // ��ų2�� ������ �� �ִ� ���������� ���� ���� -> ��Ÿ���� ��������


	virtual void OnChangeWeapon(); // ��� �޾� ������ �� ���� ��ü �Լ�
	virtual void LevelUpUpdate(); // ��� �޾� ������ �� ���� �� ���� ������Ʈ �Լ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		TArray<class USoundCue*> BGM_Sound_Arr; // �� �� �������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		TMap<FString, class USoundCue*> SoundMap; // ȿ����

	void PlaySound(FString SoundName); // ȿ���� ��� �Լ�

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // �Է� Ű���ε�
	void MoveForward(float value); // ������ �̵� �Լ�
	void MoveRight(float value); // ���������� �̵� �Լ�
	void MyJump(); // ���� �Լ�
	void BoosterOnOff(); // �ν��� ON/OFF �Լ�

private:

	/////////////////////////////* �ν��� ���� *///////////////////////////////////

	bool bIsBoosterOn; // �ν��� ON/OFF ���ο� ���� ����
	int32 SkillIndex; // ��ų1 ���� ���� �Լ�
	float BoosterGage; // �ν��� ������ ��ġ
	float MaxBoosterGage; // �ν��� ������ �ִ� ��ġ
	float BoosterGageNum; // �ν��� ������ / �ִ� �ν��� ������

	class UWidgetComponent* BoosterGage_Widget_Component; // ĳ���� �Ӹ��� �ν��� ������ ����
	TSubclassOf<class UUserWidget> BoosterGage_Widget_Class;

};
