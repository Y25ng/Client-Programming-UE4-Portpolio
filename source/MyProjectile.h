// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

class UProjetileMovementComponent;
class USphereComponent;

UCLASS()
class MYPROJECT2_API AMyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProjectile();

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		float myInitialSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		float myMaxSpeed;
	*/

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

		/*
	UFUNCTION()
		void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit);
		*/

};
