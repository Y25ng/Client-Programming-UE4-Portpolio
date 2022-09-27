// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBasicCharacter.h"
#include "SkillAttack1_Projectile.generated.h"

UCLASS()
class MYPROJECT2_API ASkillAttack1_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillAttack1_Projectile();

	class AMyBasicCharacter* MyPawn; // ��ų �߻�ü�� �߻��Ű�� �÷��̾� 
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ProjectileDamage;

	UPROPERTY(EditDefaultsOnly, Category = State)
		FName ProjectileName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		class USphereComponent* CollisionComp; // �浹ü

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		class UProjectileMovementComponent* ProjectileMovement; // �߻�ü ������

	UFUNCTION() // �ٸ� ��ü�� �¾��� �� ȣ��
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult);

	FORCEINLINE class USphereComponent* GetProjectileCollision()const { return CollisionComp; } // �浹ü ��ȯ
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement()const { return ProjectileMovement; } // �߻�ü ������ ��ȯ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* ExplodeFX; // �߻�ü�� Ÿ�Ͽ� �¾��� �� ���� Particle ȿ��

};
