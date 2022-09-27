// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkill_NotifyState.h"
#include "MyBoss.h"

void UBossSkill_NotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) // 지정 구간의 Begin 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBoss* Boss = Cast<AMyBoss>(MeshComp->GetOwner());

		if (Boss)
		{
			Boss->PlaySound("BossSkillVoice"); // 스킬 효과음 생성
			Boss->Skill_Projectile_Create(); // 스킬 발사체 생성

			if (Boss->Skill_FX)
			{
				UGameplayStatics::SpawnEmitterAtLocation(Boss->GetWorld(), Boss->Skill_FX, Boss->GetActorLocation()); // Particle 효과를 뿌려줌
			}
		}
	}
}

void UBossSkill_NotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) // 지정 구간의 End 지점에서 실행
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AMyBoss* Boss = Cast<AMyBoss>(MeshComp->GetOwner());

		if (Boss)
		{
			Boss->SetbDuringSkill(false); // 스킬 애니메이션이 진행중이 아님을 할당
		}
	}
}