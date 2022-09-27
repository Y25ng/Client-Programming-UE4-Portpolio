// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"// box 충돌체를 위한 라이브러리
#include "Components/SkeletalMeshComponent.h" // 스켈레탈 메쉬 라이브러리 
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

	USkeletalMeshComponent* GetWeaponMesh(); // WeaponMesh를 반환하는 프로퍼티 함수

	void SetOwningPawn(class ABasicCharacter* NewOwner); // 무기를 붙여줄 캐릭터를 지정할 함수
	void AttachMeshToPawn(); // 무기를 캐릭터에 붙여줄 함수
	void OnEquip(const AMyWeapon* LastWeapon); // 무기를 소켓에 장착할 함수를 호출
	void OnUnEquip(); // 무기를 해제하는 함수

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override; // 충돌체에 오버랩 발생시 호출

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		TArray<UAnimMontage*> Attack_Anim_Arr; // 공격 AnimMontage 저장

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* JumpAttack_Anim; // 점프 공격 AnimMontage 저장

	ABasicCharacter* GetMyPawn(); // 무기를 붙여줄 캐릭터 객체 반환

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh; // 무기 mesh

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		class UBoxComponent* WeaponCollision; // 무기 충돌체

protected:
	class ABasicCharacter* MyPawn; // 무기를 붙여줄 캐릭터 객체

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* CommonHitFX; // 일반공격으로 무기가 몬스터를 때렸을 때 나올 Particle 효과

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* FinalHitFX; // 콤보공격 마지막으로 무기가 몬스터를 때렸을 때 나올 Particle 효과

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
		UTexture2D* WeaponImage; // 무기 이미지

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WeaponName; // 무기 이름
};
