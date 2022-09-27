// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/BoxComponent.h"// box �浹ü�� ���� ���̺귯��

/* �������� �ֱ� ���� ���̺귯���� */
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Character.h"

#include "BasicCharacter.h"
#include "MyBasicCharacter.h"
#include "MyBot.h"

// Sets default values
AMyWeapon::AMyWeapon(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* ���� Mesh�� ���� ���� // ��ü ����, �׸���, �浹���� */

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // �浹ü off -> ������ ���� on
	RootComponent = WeaponMesh;

	/* ���� �浹ü ���� */

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision")); // �浹ü ����
	WeaponCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f)); // �浹ü ũ�� 
	WeaponCollision->AttachTo(WeaponMesh, "DamageSocket"); // �浹ü�� Ư�� ���Ͽ� ����
}

USkeletalMeshComponent* AMyWeapon::GetWeaponMesh() // WeaponMesh�� ��ȯ�ϴ� ������Ƽ �Լ�
{
	return WeaponMesh;
}

void AMyWeapon::SetOwningPawn(ABasicCharacter* NewOwner) // ���⸦ �ٿ��� ĳ���� ��ȯ
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AMyWeapon::AttachMeshToPawn() // ���⸦ ĳ���Ϳ� �ٿ��� �Լ�
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->AttachTo(PawnMesh, AttachPoint); // ���� ���Ͽ� ���⸦ �ٿ���
	}
}

void AMyWeapon::OnEquip(const AMyWeapon* LastWeapon) // ���⸦ ���Ͽ� �������� �Լ��� ȣ��
{
	AttachMeshToPawn();
	WeaponMesh->SetHiddenInGame(false);
}

void AMyWeapon::OnUnEquip() // ���⸦ ���Ͽ� �������� �Լ��� ȣ��
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh->SetHiddenInGame(true);
}

void AMyWeapon::NotifyActorBeginOverlap(AActor* OtherActor) // �浹 ���� �Լ�
{
	if ((OtherActor->IsA(ABasicCharacter::StaticClass()) && MyPawn) // ���⿡ ���� ���� Pawn�� ���
		&& MyPawn->GetbIsDuringAttack() == true && OtherActor != MyPawn && MyPawn->GetbDamagePossible() == true // ������ AND ����������
		&& !(MyPawn->GetMyCharacterName() == "Bot" && OtherActor->IsA(AMyBot::StaticClass()))) // ���� ������ ������ ��� ����
	{
		float TempDamage; // ������ ������ �Ű������� �־��� �ӽ� ����

		if (MyPawn->GetMyCharacterName() == "Player") // ���� ������ �÷��̾��� ���� ������
		{
			TempDamage = MyPawn->Get_AttackPower();

			if (MyPawn->GetbFinalAttack() == true) // �޺� ������ ������ �� �߰� �������� ������
				TempDamage += TempDamage * 0.2f;

			AMyBasicCharacter* TempMyPawn = Cast<AMyBasicCharacter>(MyPawn);
			TempMyPawn->PlaySound(("AttackCollision")); //Ÿ�� �� ��� �� ȿ����
		}
		else // ���� ������ �÷��̾ �ƴ� ���� ������
		{
			TempDamage = MyPawn->Get_AttackPower();

			AMyBot* TempMyPawn = Cast<AMyBot>(MyPawn);
			TempMyPawn->PlaySound(("AttackCollision")); // Ÿ�� �� ��� �� ȿ����
		}

			UGameplayStatics::ApplyDamage(OtherActor, TempDamage, nullptr, this, UDamageType::StaticClass()); //  �������� ����

		if (MyPawn->GetbFinalAttack())
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FinalHitFX, GetActorLocation());
		}
		else
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CommonHitFX, GetActorLocation());
		}
	}
}

ABasicCharacter* AMyWeapon::GetMyPawn()
{
	return MyPawn;
}
