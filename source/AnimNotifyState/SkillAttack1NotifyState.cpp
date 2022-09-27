// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillAttack1NotifyState.h"
#include "MyBasicCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void USkillAttack1NotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{

}

void USkillAttack1NotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr) 
	{
		AMyBasicCharacter* Player = Cast< AMyBasicCharacter>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			if (Player->GetSkillIndex() == 1 && Player->SkillAttack1_FX != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(), Player->SkillAttack1_FX, Player->GetCurrentWeapon()->GetActorLocation());
				// ���ϴ� �������� Particle ���

				// ī�޶� ����ũ
				Player->GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(Player->CameraShakeClass);

				Player->SkillAttack1_Projectile_Create(); // ��ų �߻�ü ����

				AMyBasicCharacter* MyPlayer = Cast<AMyBasicCharacter>(Player);

				if (MyPlayer)
				{
					MyPlayer->PlaySound("Skill1"); // Skill1 ȿ���� ���
				}
			}
			else if (Player->GetSkillIndex() == 2 && Player->SkillAttack2_FX != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(), Player->SkillAttack2_FX, Player->GetCurrentWeapon()->GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(), Player->SkillAttack2_Explode_FX, Player->GetCurrentWeapon()->GetActorLocation());
				// ���ϴ� �������� Particle ���

				// ī�޶� ����ũ
				Player->GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(Player->CameraShakeClass2);

				Player->SkillAttack2_Projectile_Create(); // ��ų �߻�ü ����

				AMyBasicCharacter* MyPlayer = Cast<AMyBasicCharacter>(Player);

				if (MyPlayer)
				{
					MyPlayer->PlaySound("Skill2"); // Skill2 ȿ���� ���
				}
			}
		}
	}
}