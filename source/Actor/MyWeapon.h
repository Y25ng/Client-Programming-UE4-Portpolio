// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"// box �浹ü�� ���� ���̺귯��
#include "Components/SkeletalMeshComponent.h" // ���̷�Ż �޽� ���̺귯�� 
#include "MyWeapon.h"
#include "BasicCharacter.h"

#include "MyWeapon.generated.h"

UCLASS()
class MYPROJECT2_API AMyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon(const class FObjectInitializer& ObjectInitializer);

	USkeletalMeshComponent* GetWeaponMesh(); // WeaponMesh�� ��ȯ�ϴ� ������Ƽ �Լ�

	void SetOwningPawn(class ABasicCharacter* NewOwner); // ���⸦ �ٿ��� ĳ���͸� ������ �Լ�
	void AttachMeshToPawn(); // ���⸦ ĳ���Ϳ� �ٿ��� �Լ�
	void OnEquip(const AMyWeapon* LastWeapon); // ���⸦ ���Ͽ� ������ �Լ��� ȣ��
	void OnUnEquip(); // ���⸦ �����ϴ� �Լ�

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override; // �浹ü�� ������ �߻��� ȣ��

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		TArray<UAnimMontage*> Attack_Anim_Arr; // ���� AnimMontage ����

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* JumpAttack_Anim; // ���� ���� AnimMontage ����

	ABasicCharacter* GetMyPawn(); // ���⸦ �ٿ��� ĳ���� ��ü ��ȯ

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh; // ���� mesh

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		class UBoxComponent* WeaponCollision; // ���� �浹ü

protected:
	class ABasicCharacter* MyPawn; // ���⸦ �ٿ��� ĳ���� ��ü

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* CommonHitFX; // �Ϲݰ������� ���Ⱑ ���͸� ������ �� ���� Particle ȿ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* FinalHitFX; // �޺����� ���������� ���Ⱑ ���͸� ������ �� ���� Particle ȿ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
		UTexture2D* WeaponImage; // ���� �̹���

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WeaponName; // ���� �̸�
};
