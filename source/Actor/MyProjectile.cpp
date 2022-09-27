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
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectile::OnOverlapBegin); // �浹�� Ư�� �Լ� ȣ��
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.0f;

	// ProjectileDamage = 5.0f; // �߻�ü�� �浹 �� �� ������
}

// �߻�ü�� �浹�� �߻����� �� ȣ��
void AMyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(AMyBasicCharacter::StaticClass())) // �浹�� ���� �÷��̾� ĳ���Ͷ��
		{
			UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, nullptr, this, UDamageType::StaticClass()); // ������ ����

			if (ExplodeFX != nullptr) 
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeFX, GetActorLocation()); // �浹�� Particle ȿ���� �ѷ���
			}

			AMyBasicCharacter* TempMyPawn = Cast<AMyBasicCharacter>(OtherActor);
			if (TempMyPawn != nullptr)
				TempMyPawn->PlaySound(("BotBomb")); // �÷��̾�� Ÿ�ݽ� ����� ȿ����

			Destroy(); // ���� �߻�ü�� ������
		}
	}
}

/*
void AMyProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit)
{
}
*/