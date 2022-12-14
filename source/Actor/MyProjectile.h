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
		class USphereComponent* CollisionComp; // 충돌체

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		class UProjectileMovementComponent* ProjectileMovement; // 발사체 움직임

	UFUNCTION() // 다른 물체에 맞았을 때 호출
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult);

	FORCEINLINE class USphereComponent* GetProjectileCollision()const { return CollisionComp; } // 충돌체 반환
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement()const { return ProjectileMovement; } // 발사체 움직임 반환

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* ExplodeFX; // 발사체가 타켓에 맞았을 때 나올 Particle 효과

		/*
	UFUNCTION()
		void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit);
		*/

};
