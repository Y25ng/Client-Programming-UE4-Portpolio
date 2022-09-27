// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"
#include "Components/SphereComponent.h"
#include "MyBasicCharacter.h"
#include "Engine.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Bot_Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectile::OnOverlapBegin); // 충돌시 특정 함수 호출
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.0f;

	// ProjectileDamage = 5.0f; // 발사체가 충돌 시 줄 데미지
}

// 발사체에 충돌이 발생했을 때 호출
void AMyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // 충돌한 것이 플레이어 캐릭터라면
		{
			UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, nullptr, this, UDamageType::StaticClass()); // 데미지 적용

			if (ExplodeFX != nullptr) 
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeFX, GetActorLocation()); // 충돌시 Particle 효과를 뿌려줌
			}

			AMyBasicCharacter* TempMyPawn = Cast<AMyBasicCharacter>(OtherActor);
			if (TempMyPawn != nullptr)
				TempMyPawn->PlaySound(("BotBomb")); // 플레이어에게 타격시 재생될 효과음

			Destroy(); // 이후 발사체를 없애줌
		}
	}
}

/*
void AMyProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit)
{
}
*/