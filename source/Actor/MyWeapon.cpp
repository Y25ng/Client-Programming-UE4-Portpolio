// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/BoxComponent.h"// box 충돌체를 위한 라이브러리

/* 데미지를 주기 위한 라이브러리들 */
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

	/* 무기 Mesh에 관한 설정 // 객체 생성, 그림자, 충돌여부 */

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 충돌체 off -> 공격할 때만 on
	RootComponent = WeaponMesh;

	/* 무기 충돌체 설정 */

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision")); // 충돌체 생성
	WeaponCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f)); // 충돌체 크기 
	WeaponCollision->AttachTo(WeaponMesh, "DamageSocket"); // 충돌체를 특정 소켓에 부착
}

USkeletalMeshComponent* AMyWeapon::GetWeaponMesh() // WeaponMesh를 반환하는 프로퍼티 함수
{
	return WeaponMesh;
}

void AMyWeapon::SetOwningPawn(ABasicCharacter* NewOwner) // 무기를 붙여줄 캐릭터 반환
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AMyWeapon::AttachMeshToPawn() // 무기를 캐릭터에 붙여줄 함수
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->AttachTo(PawnMesh, AttachPoint); // 무기 소켓에 무기를 붙여줌
	}
}

void AMyWeapon::OnEquip(const AMyWeapon* LastWeapon) // 무기를 소켓에 장착해줄 함수를 호출
{
	AttachMeshToPawn();
	WeaponMesh->SetHiddenInGame(false);
}

void AMyWeapon::OnUnEquip() // 무기를 소켓에 장착해줄 함수를 호출
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh->SetHiddenInGame(true);
}

void AMyWeapon::NotifyActorBeginOverlap(AActor* OtherActor) // 충돌 감지 함수
{
	if ((OtherActor->IsA(ABasicCharacter::StaticClass()) && MyPawn) // 무기에 맞은 것이 Pawn일 경우
		&& MyPawn->GetbIsDuringAttack() == true && OtherActor != MyPawn && MyPawn->GetbDamagePossible() == true // 공격중 AND 데미지가능
		&& !(MyPawn->GetMyCharacterName() == "Bot" && OtherActor->IsA(AMyBot::StaticClass()))) // 봇이 봇에게 공격한 경우 제외
	{
		float TempDamage; // 적용할 데미지 매개변수로 넣어줄 임시 변수

		if (MyPawn->GetMyCharacterName() == "Player") // 무기 주인이 플레이어일 때의 데미지
		{
			TempDamage = MyPawn->Get_AttackPower();

			if (MyPawn->GetbFinalAttack() == true) // 콤보 마지막 공격일 시 추가 데미지를 더해줌
				TempDamage += TempDamage * 0.2f;

			AMyBasicCharacter* TempMyPawn = Cast<AMyBasicCharacter>(MyPawn);
			TempMyPawn->PlaySound(("AttackCollision")); //타격 시 재생 될 효과음
		}
		else // 무기 주인이 플레이어가 아닐 때의 데미지
		{
			TempDamage = MyPawn->Get_AttackPower();

			AMyBot* TempMyPawn = Cast<AMyBot>(MyPawn);
			TempMyPawn->PlaySound(("AttackCollision")); // 타격 시 재생 될 효과음
		}

			UGameplayStatics::ApplyDamage(OtherActor, TempDamage, nullptr, this, UDamageType::StaticClass()); //  데미지를 적용

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
