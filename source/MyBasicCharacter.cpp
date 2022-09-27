// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasicCharacter.h"

#include "GameFramework/SpringArmComponent.h" // ī�޶� ������ ���̺귯��
#include "Camera/CameraComponent.h" // ī�޶� ���̺귯��
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameHUD_UI.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Perception/AISense_Sight.h"
#include "MySaveGame.h"
#include "Engine.h"

#include "UI_BoosterGage_Widget.h"

AMyBasicCharacter::AMyBasicCharacter()
{
	////////////////////////////////// ī�޶� ������ ///////////////////////////////////////////

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // ī�޶� ������ ��ü ����
	CameraBoom->SetupAttachment(RootComponent); // ĳ���� �߾ӿ� ī�޶� �����븦 �ٿ���
	CameraBoom->TargetArmLength = 800.0f; // ī�޶� ������ ����
	CameraBoom->bUsePawnControlRotation = true; // ĳ���͸� �������� ī�޶� �����밡 ȸ��
	CameraBoom->bEnableCameraLag = true; // ī�޶� ĳ���͸� �ణ �����Ǿ ����ٴϵ��� ����
	CameraBoom->CameraLagSpeed = 5.0f; // ī�޶� ���� �ӵ�

	////////////////////////////////// ī�޶� ///////////////////////////////////////////

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // ī�޶� ��ü ����
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // ī�޶� �����뿡 �ٿ���
	FollowCamera->bUsePawnControlRotation = false;

	////////////////////////////////// ����Ű & ���콺 ���� ///////////////////////////////////////////////

	/* �չ��� ����Ű�� �����ϰ� �ٸ� ����Ű�� ��� ���콺 ���⿡ ������ ���� �ʰ� ���� */

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // ĳ���Ͱ� �Էµ� ����Ű ������ ���ϰ� ����

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	GetCharacterMovement()->MaxWalkSpeed = 300.0f; // ĳ���� �ְ� �ӵ�
	GetCharacterMovement()->JumpZVelocity = 700.0f; // ���� ����
	JumpMaxCount = 1; // ���� ���� ���� Ƚ��

	MyCharacterName = "Player"; // Pawn ���� -> BasicCharacter���� ���


	////////////////////////////////* �ν��� ���� *//////////////////////////////////////////

	MaxBoosterGage = 10.f;
	BoosterGage = MaxBoosterGage;

	BoosterGage_Widget_Component = CreateDefaultSubobject <UWidgetComponent>(TEXT("BoosterGageValue")); // �ν��� ������ ���� ������Ʈ ��ü ����

	if (BoosterGage_Widget_Component != nullptr) // �ν��� ������ ���� ���
	{
		BoosterGage_Widget_Component->SetupAttachment(RootComponent);
		BoosterGage_Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		BoosterGage_Widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget>BoosterWidget_class(TEXT("/Game/Blueprints/UI/BoosterGage"));

		if (BoosterWidget_class.Succeeded())
		{
			BoosterGage_Widget_Component->SetWidgetClass(BoosterWidget_class.Class);
			BoosterGage_Widget_Component->bHiddenInGame = true;
		}
	}

	// ��Ÿ���� �ִ� ��ų -> ��Ÿ���� ���� ��밡�������� �Ҵ�޴� ������ �ʱ�ȭ

	bSkill2Possible = true;
}

void AMyBasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �ʿ� ���� ��� ���� ���
	if (BGM_Sound_Arr[DungeonLevel])
		UGameplayStatics::SpawnSoundAttached(BGM_Sound_Arr[DungeonLevel], RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
}

void AMyBasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BoosterGageNum = BoosterGage / MaxBoosterGage;

	auto const BoosterGageUW = Cast<UUI_BoosterGage_Widget>(BoosterGage_Widget_Component->GetUserWidgetObject());
	if (BoosterGageUW)
	{
		// BoosterGage/MaxBoosterGage ���� Widget�� ProgressBar ��ġ�� �Ҵ�
		BoosterGageUW->set_bar_value_percent(BoosterGageNum);
	}

	if (bIsBoosterOn == true) // �ν��� On ���¶��
	{
		if (GetVelocity().Size() > 0.f)
		{
			BoosterGage_Widget_Component->bHiddenInGame = false;

			if (BoosterGage > 0.f) // �ν��� �������� 0 �̻��̶�� �ð��� ���� ������ �ν�Ʈ �������� ���ҽ�����
				BoosterGage -= 1.f * DeltaTime;
			else // �ν��� �������� 0 ���϶�� �ν��� Off ���·� �������
			{
				GetCharacterMovement()->MaxWalkSpeed = 500.f;
				bIsBoosterOn = false;
			}
		}
		else // �������� �ʰ� �����ִٸ� �ν��� �������� ȸ��������
		{
			if (BoosterGage < MaxBoosterGage)
				BoosterGage += 1.5f * DeltaTime;
			else if(BoosterGage >= MaxBoosterGage)
				BoosterGage_Widget_Component->bHiddenInGame = true;
		}
	}
	else // �ν��� Off ���¶��
	{
		if (BoosterGage < MaxBoosterGage)
		{
			if (GetVelocity().Size() == 0.f)
				BoosterGage += 2.f * DeltaTime;
		}
		else if (BoosterGage >= MaxBoosterGage)
		{
			BoosterGage_Widget_Component->bHiddenInGame = true;	
		}
	}

	/* EXP�� 100�ۼ�Ʈ �̻��� �Ǿ��� �� */
	if (MyEXP >= MyMaxEXP)
	{
		this->LevelUpUpdate();
	}
}

void AMyBasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // Ű���ε� �Լ�
{
	ABasicCharacter::SetupPlayerInputComponent(PlayerInputComponent); // ���� Ŭ���� Ű���ε� ȣ��

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyBasicCharacter::MoveForward); // MoveForward ���۽�  MoveForward() �Լ� ����
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyBasicCharacter::MoveRight); // MoveRight ���� �� MoveRight() �Լ� ����

	// �¿� ȸ�� ���ε�
	// AddControllerYawInput : ���콺 �¿� ȸ�� ���� �⺻ ���� �Լ�
	PlayerInputComponent->BindAxis("Turn", this, &AMyBasicCharacter::AddControllerYawInput);

	// ���� ȸ�� ���ε�
	// AddControllerPitchInput : ���콺 ���� ȸ�� ���� �⺻ ���� �Լ�
	PlayerInputComponent->BindAxis("LookUp", this, &AMyBasicCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("RunFaster", IE_Pressed, this, &AMyBasicCharacter::BoosterOnOff); // �ν��� On/Off
	PlayerInputComponent->BindAction("WeaponChange", IE_Pressed, this, &AMyBasicCharacter::OnChangeWeapon); // ���� ��ü

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyBasicCharacter::MyJump); // ���� 

	PlayerInputComponent->BindAction("SkillAttack1", IE_Pressed, this, &AMyBasicCharacter::SkillAttack1); // ��ų1 ����
	PlayerInputComponent->BindAction("SkillAttack2", IE_Pressed, this, &AMyBasicCharacter::SkillAttack2); // ��ų2 ����
}

void AMyBasicCharacter::MoveForward(float value) // ������ �̵� �Լ�
{
	if (Controller != nullptr && value != 0.0f && bIsDuringAttack == false && bIsStarting == false && bIsDuringJumpEnd == false) 
		// ������ X & ������ X & ���� End ������ X �� �� ���� 
	{
		StopAnimMontage(); // �ٸ� �ִϸ��̼��� �������̾��ٸ� ������
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, value);
		SetComboAttack_Num(0); // �޺� ���� ī��Ʈ�� 0���� �ʱ�ȭ
	}
}

void AMyBasicCharacter::MoveRight(float value) // ���������� �̵� �Լ�
{
	if (Controller != nullptr && value != 0.0f && bIsDuringAttack == false && bIsStarting == false && bIsDuringJumpEnd == false) 
		// ������ X & ������ X & ���� End ������ X �� �� ���� 
	{
		StopAnimMontage(); // �ٸ� �ִϸ��̼��� �������̾��ٸ� ������
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, value);
		SetComboAttack_Num(0); // �޺� ���� ī��Ʈ�� 0���� �ʱ�ȭ
	}
}

void AMyBasicCharacter::MyJump()
{
	if (bIsStarting == false) // ���� ���� Anim�� ���������� ���� �� ���� ����
	{
		ACharacter::Jump(); // ACharacter�� Jump�� ��ӹ޾� ���
		ComboAttack_Num = 0; // �⺻ ���� �޺� �� 0���� �ʱ�ȭ

		PlaySound("JumpStart"); // ���� �Ҹ� ���
	}
}

void AMyBasicCharacter::BoosterOnOff() // �ν��� On/Off �Լ�
{
	if (bIsBoosterOn == false && BoosterGage > 0.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 700.0f;
		bIsBoosterOn = true;
		BoosterGage_Widget_Component->bHiddenInGame = false;
	}
	else if(bIsBoosterOn == true)
	{
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		bIsBoosterOn = false;
	}
}


void AMyBasicCharacter::PostInitializeComponents() // ���⸦ ĳ���Ϳ� �ٿ��� �Լ�
{
	Super::PostInitializeComponents();
	SpawndefaultInventory(); // �κ��丮�� �ִ� ���⸦ �ҷ�����
}


void AMyBasicCharacter::PlaySound(FString SoundName) // ȿ���� ��� �Լ�
{
	if(SoundMap.Find(SoundName) != nullptr)
		UGameplayStatics::SpawnSoundAttached(SoundMap[SoundName], RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
}

void AMyBasicCharacter::OnChangeWeapon()
{
	ABasicCharacter::OnChangeWeapon(); // �θ� Ŭ������ ���� ��ü �Լ� ȣ��
	PlaySound("WeaponChange"); // ���� ��ü ȿ���� ���
}

void AMyBasicCharacter::LevelUpUpdate()
{
	ABasicCharacter::LevelUpUpdate(); // �θ� Ŭ������ ������ �Լ� ȣ��
	PlaySound("LevelUp"); // ������ ȿ���� ���
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////* ��ų ���� �Լ� *///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


int32 AMyBasicCharacter::GetSkillIndex()
{
	return SkillIndex;
}

void AMyBasicCharacter::SkillAttack1() // ��ų1 ���� �Լ�
{
	SkillIndex = 1;
	CharacterCurrentSkill = CharacterSkillTable->FindRow<FCharacterSkill>(*FString::FromInt(SkillIndex), TEXT(""));

	if (CharacterCurrentSkill != nullptr)
	{
		if (MyLevel < CharacterCurrentSkill->ActivationLevel || MyMP < CharacterCurrentSkill->ConsumeMP)
			return; // �÷��̾� ������ ��ų Ȱ��ȭ �������� ���� �� OR �÷��̾� MP�� ������ �� -> ��ų�� �������� ����
	}

	if (bIsDuringAttack == false && bIsStarting == false) // ���������� ���� �� && ���� ���� Anim�� ���������� ���� ��
	{
		if (GetMovementComponent()->IsFalling() == false) // ���߿� ���� ���� ��
		{
			PlayAnimMontage(SkillAttack1_Anim); // ��ų AnimMontage�� ����
			bIsDuringAttack = true; // ���������� ���θ� ��Ÿ���� ������ true �Ҵ�
			MyMP -= CharacterCurrentSkill->ConsumeMP; // �ش� ��ų MP��ŭ �÷��̾� MP ����
		}
	}
}

void AMyBasicCharacter::SkillAttack1_Projectile_Create() // ��ų1 �ߵ� �� ���� �߻�ü�� ���� �� �߻�
{
	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(0.0f, 0.0f, 90.f));
	UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		float temp = 0;

		for (int32 i = 0; i < 20; i++) // 45�� �������� ��� �������� �߻�ü�� �߻�
		{
			temp = 18.f * i;

			FRotator TempSpawnRotation = SpawnRotation + FRotator(0.f, temp, 0.0f);
			ASkillAttack1_Projectile* Skill1Projectile = World->SpawnActor<ASkillAttack1_Projectile>(Skill1_Projectile, SpawnLocation, TempSpawnRotation);
			Skill1Projectile->ProjectileDamage = AttackPower * CharacterCurrentSkill->SkillPower;
			Skill1Projectile->MyPawn = this; // �߻�ü�� �߻��Ű�� �÷��̾ �Ҵ�
		}
	}
}

void AMyBasicCharacter::SkillAttack2() // ��ų2 ���� �Լ�
{
	SkillIndex = 2;
	CharacterCurrentSkill = CharacterSkillTable->FindRow<FCharacterSkill>(*FString::FromInt(SkillIndex), TEXT(""));

	if (bSkill2Possible == false) // ��Ÿ���� �Ϸ���� ���� ���¿����� ����X
		return;

	if (CharacterCurrentSkill != nullptr)
	{
		if (MyLevel < CharacterCurrentSkill->ActivationLevel || MyMP < CharacterCurrentSkill->ConsumeMP)
			return; // �÷��̾� ������ ��ų Ȱ��ȭ �������� ���� �� OR �÷��̾� MP�� ������ �� -> ��ų�� �������� ����
	}

	if (bIsDuringAttack == false && bIsStarting == false) // ���������� ���� �� && ���� ���� Anim�� ���������� ���� ��
	{
		if (GetMovementComponent()->IsFalling() == false) // ���߿� ���� ���� ��
		{
			bSkill2Possible = false;

			SkillIndex = 2;
			CharacterCurrentSkill = CharacterSkillTable->FindRow<FCharacterSkill>(*FString::FromInt(SkillIndex), TEXT(""));

			FTimerHandle TH_Skill2CoolTime;
			GetWorldTimerManager().SetTimer(TH_Skill2CoolTime, this, &AMyBasicCharacter::CoolTimeEnd, CharacterCurrentSkill->CoolTime, false);

			PlayAnimMontage(SkillAttack2_Anim); // ��ų AnimMontage�� ����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillAttack2_WarmUp_FX, GetCurrentWeapon()->GetActorLocation());
			// ���ϴ� �������� Particle ���
			bIsDuringAttack = true; // ���������� ���θ� ��Ÿ���� ������ true �Ҵ�
			MyMP -= CharacterCurrentSkill->ConsumeMP; // �ش� ��ų MP��ŭ �÷��̾� MP ����
		}
	}
}

void AMyBasicCharacter::SkillAttack2_Projectile_Create() // ��ų2 �ߵ� �� ���� �߻�ü�� ���� �� �߻�
{
	FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(0.0f, 0.0f, 90.f));
	UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		float temp = 0;

		for (int32 i = 0; i < 20; i++) // 45�� �������� ��� �������� �߻�ü�� �߻�
		{
			temp = 18.f * i;

			FRotator TempSpawnRotation = SpawnRotation + FRotator(0.f, temp, 0.0f);
			ASkillAttack1_Projectile* Skill2Projectile = World->SpawnActor<ASkillAttack1_Projectile>(Skill2_Projectile, SpawnLocation, TempSpawnRotation);
			Skill2Projectile->ProjectileDamage = AttackPower * CharacterCurrentSkill->SkillPower;
			Skill2Projectile->MyPawn = this; // �߻�ü�� �߻��Ű�� �÷��̾ �Ҵ�
		}
	}
}

void AMyBasicCharacter::CoolTimeEnd() // ��Ÿ���� �ִ� ��ų2 ��� �� ��Ÿ�� ���Ḧ �˸��� �Լ�
{
	bSkill2Possible = true;
}





