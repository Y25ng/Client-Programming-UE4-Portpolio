// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkill_NotifyState.h"
#include "MyBoss.h"

void UBossSkill_NotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // ���� ������ Begin �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBoss* Boss = Cast<AMyBoss>(MeshComp->GetOwner());

		if (Boss)
		{
			Boss->PlaySound("BossSkillVoice"); // ��ų ȿ���� ����
			Boss->Skill_Projectile_Create(); // ��ų �߻�ü ����

			if (Boss->Skill_FX)
			{
				UGameplayStatics::SpawnEmitterAtLocation(Boss->GetWorld(), Boss->Skill_FX, Boss->GetActorLocation()); // Particle ȿ���� �ѷ���
			}
		}
	}
}

void UBossSkill_NotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // ���� ������ End �������� ����
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBoss* Boss = Cast<AMyBoss>(MeshComp->GetOwner());

		if (Boss)
		{
			Boss->SetbDuringSkill(false); // ��ų �ִϸ��̼��� �������� �ƴ��� �Ҵ�
		}
	}
}