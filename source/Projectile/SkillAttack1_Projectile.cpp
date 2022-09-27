// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillAttack1_Projectile.h"
#include "Components/SphereComponent.h"
#include "BasicCharacter.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"
#include "Engine.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASkillAttack1_Projectile::ASkillAttack1_Projectile()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Skill1_Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASkillAttack1_Projectile::OnOverlapBegin); // 충돌시 특정 함수 호출
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 4000.0f;
	ProjectileMovement->MaxSpeed = 4000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 0.1f;
}

// 발사체에 충돌이 발생했을 때 호출
void ASkillAttack1_Projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(AMyBot::StaticClass())) // 충돌한 것이 봇이라면
		{
			UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, nullptr, this, UDamageType::StaticClass()); // 데미지 적용

			if (ExplodeFX != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeFX, GetActorLocation()); // 충돌시 Particle 효과를 뿌려줌
			}
			if (MyPawn != nullptr)
			{
				AMyBasicCharacter* TempMyPawn = Cast<AMyBasicCharacter>(MyPawn);
				if(TempMyPawn != nullptr)
					TempMyPawn->PlaySound(("AttackCollision")); // 몬스터에게 타격 시 재생 될 효과음
			}
		}
	}
}

