// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasicCharacter.h"

#include "GameFramework/SpringArmComponent.h" // 카메라 지지대 라이브러리
#include "Camera/CameraComponent.h" // 카메라 라이브러리
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
	////////////////////////////////// 카메라 지지대 ///////////////////////////////////////////

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // 카메라 지지대 객체 생성
	CameraBoom->SetupAttachment(RootComponent); // 캐릭터 중앙에 카메라 지지대를 붙여줌
	CameraBoom->TargetArmLength = 800.0f; // 카메라 지지대 길이
	CameraBoom->bUsePawnControlRotation = true; // 캐릭터를 기준으로 카메라 지지대가 회전
	CameraBoom->bEnableCameraLag = true; // 카메라가 캐릭터를 약간 지연되어서 따라다니도록 해줌
	CameraBoom->CameraLagSpeed = 5.0f; // 카메라 지연 속도

	////////////////////////////////// 카메라 ///////////////////////////////////////////

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // 카메라 객체 생성
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 카메라를 지지대에 붙여줌
	FollowCamera->bUsePawnControlRotation = false;

	////////////////////////////////// 방향키 & 마우스 설정 ///////////////////////////////////////////////

	/* 앞방향 방향키를 제외하고 다른 방향키의 경우 마우스 방향에 영향을 받지 않게 해줌 */

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 입력된 방향키 방향을 향하게 해줌

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	GetCharacterMovement()->MaxWalkSpeed = 300.0f; // 캐릭터 최고 속도
	GetCharacterMovement()->JumpZVelocity = 700.0f; // 점프 높이
	JumpMaxCount = 1; // 연속 점프 가능 횟수

	MyCharacterName = "Player"; // Pawn 종류 -> BasicCharacter에서 상속


	////////////////////////////////* 부스터 관련 *//////////////////////////////////////////

	MaxBoosterGage = 10.f;
	BoosterGage = MaxBoosterGage;

	BoosterGage_Widget_Component = CreateDefaultSubobject <UWidgetComponent>(TEXT("BoosterGageValue")); // 부스터 게이지 위젯 컴포넌트 객체 생성

	if (BoosterGage_Widget_Component != nullptr) // 부스터 게이지 위젯 출력
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

	// 쿨타임이 있는 스킬 -> 쿨타임이 끝나 사용가능한지를 할당받는 변수들 초기화

	bSkill2Possible = true;
}

void AMyBasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 맵에 따른 배경 음악 재생
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
		// BoosterGage/MaxBoosterGage 값을 Widget의 ProgressBar 수치에 할당
		BoosterGageUW->set_bar_value_percent(BoosterGageNum);
	}

	if (bIsBoosterOn == true) // 부스터 On 상태라면
	{
		if (GetVelocity().Size() > 0.f)
		{
			BoosterGage_Widget_Component->bHiddenInGame = false;

			if (BoosterGage > 0.f) // 부스터 게이지가 0 이상이라면 시간이 지날 때마다 부스트 게이지를 감소시켜줌
				BoosterGage -= 1.f * DeltaTime;
			else // 부스터 게이지가 0 이하라면 부스터 Off 상태로 만들어줌
			{
				GetCharacterMovement()->MaxWalkSpeed = 500.f;
				bIsBoosterOn = false;
			}
		}
		else // 움직이지 않고 멈춰있다면 부스터 게이지를 회복시켜줌
		{
			if (BoosterGage < MaxBoosterGage)
				BoosterGage += 1.5f * DeltaTime;
			else if(BoosterGage >= MaxBoosterGage)
				BoosterGage_Widget_Component->bHiddenInGame = true;
		}
	}
	else // 부스터 Off 상태라면
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

	/* EXP가 100퍼센트 이상이 되었을 때 */
	if (MyEXP >= MyMaxEXP)
	{
		this->LevelUpUpdate();
	}
}

void AMyBasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // 키바인딩 함수
{
	ABasicCharacter::SetupPlayerInputComponent(PlayerInputComponent); // 상위 클래스 키바인딩 호출

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyBasicCharacter::MoveForward); // MoveForward 동작시  MoveForward() 함수 실행
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyBasicCharacter::MoveRight); // MoveRight 동작 시 MoveRight() 함수 실행

	// 좌우 회전 바인딩
	// AddControllerYawInput : 마우스 좌우 회전 구현 기본 내장 함수
	PlayerInputComponent->BindAxis("Turn", this, &AMyBasicCharacter::AddControllerYawInput);

	// 상하 회전 바인딩
	// AddControllerPitchInput : 마우스 상하 회전 구현 기본 내장 함수
	PlayerInputComponent->BindAxis("LookUp", this, &AMyBasicCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("RunFaster", IE_Pressed, this, &AMyBasicCharacter::BoosterOnOff); // 부스터 On/Off
	PlayerInputComponent->BindAction("WeaponChange", IE_Pressed, this, &AMyBasicCharacter::OnChangeWeapon); // 무기 교체

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyBasicCharacter::MyJump); // 점프 

	PlayerInputComponent->BindAction("SkillAttack1", IE_Pressed, this, &AMyBasicCharacter::SkillAttack1); // 스킬1 공격
	PlayerInputComponent->BindAction("SkillAttack2", IE_Pressed, this, &AMyBasicCharacter::SkillAttack2); // 스킬2 공격
}

void AMyBasicCharacter::MoveForward(float value) // 앞으로 이동 함수
{
	if (Controller != nullptr && value != 0.0f && bIsDuringAttack == false && bIsStarting == false && bIsDuringJumpEnd == false) 
		// 공격중 X & 시작중 X & 점프 End 진행중 X 일 때 실행 
	{
		StopAnimMontage(); // 다른 애니메이션이 실행중이었다면 멈춰줌
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, value);
		SetComboAttack_Num(0); // 콤보 어택 카운트를 0으로 초기화
	}
}

void AMyBasicCharacter::MoveRight(float value) // 오른쪽으로 이동 함수
{
	if (Controller != nullptr && value != 0.0f && bIsDuringAttack == false && bIsStarting == false && bIsDuringJumpEnd == false) 
		// 공격중 X & 시작중 X & 점프 End 진행중 X 일 때 실행 
	{
		StopAnimMontage(); // 다른 애니메이션이 실행중이었다면 멈춰줌
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, value);
		SetComboAttack_Num(0); // 콤보 어택 카운트를 0으로 초기화
	}
}

void AMyBasicCharacter::MyJump()
{
	if (bIsStarting == false) // 레벨 시작 Anim이 진행중이지 않을 때 점프 수행
	{
		ACharacter::Jump(); // ACharacter의 Jump를 상속받아 사용
		ComboAttack_Num = 0; // 기본 공격 콤보 수 0으로 초기화

		PlaySound("JumpStart"); // 점프 소리 출력
	}
}

void AMyBasicCharacter::BoosterOnOff() // 부스터 On/Off 함수
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


void AMyBasicCharacter::PostInitializeComponents() // 무기를 캐릭터에 붙여줄 함수
{
	Super::PostInitializeComponents();
	SpawndefaultInventory(); // 인벤토리에 있는 무기를 불러와줌
}


void AMyBasicCharacter::PlaySound(FString SoundName) // 효과음 재생 함수
{
	if(SoundMap.Find(SoundName) != nullptr)
		UGameplayStatics::SpawnSoundAttached(SoundMap[SoundName], RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
}

void AMyBasicCharacter::OnChangeWeapon()
{
	ABasicCharacter::OnChangeWeapon(); // 부모 클래스의 무기 교체 함수 호출
	PlaySound("WeaponChange"); // 무기 교체 효과음 재생
}

void AMyBasicCharacter::LevelUpUpdate()
{
	ABasicCharacter::LevelUpUpdate(); // 부모 클래스의 레벨업 함수 호출
	PlaySound("LevelUp"); // 레벨업 효과음 재생
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////* 스킬 관련 함수 *///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


int32 AMyBasicCharacter::GetSkillIndex()
{
	return SkillIndex;
}

void AMyBasicCharacter::SkillAttack1() // 스킬1 실행 함수
{
	SkillIndex = 1;
	CharacterCurrentSkill = CharacterSkillTable->FindRow<FCharacterSkill>(*FString::FromInt(SkillIndex), TEXT(""));

	if (CharacterCurrentSkill != nullptr)
	{
		if (MyLevel < CharacterCurrentSkill->ActivationLevel || MyMP < CharacterCurrentSkill->ConsumeMP)
			return; // 플레이어 레벨이 스킬 활성화 레벨보다 낮을 시 OR 플레이어 MP가 부족할 시 -> 스킬을 실행하지 않음
	}

	if (bIsDuringAttack == false && bIsStarting == false) // 공격중이지 않을 때 && 레벨 시작 Anim이 진행중이지 않을 때
	{
		if (GetMovementComponent()->IsFalling() == false) // 공중에 있지 않을 때
		{
			PlayAnimMontage(SkillAttack1_Anim); // 스킬 AnimMontage를 실행
			bIsDuringAttack = true; // 공격중인지 여부를 나타내는 변수에 true 할당
			MyMP -= CharacterCurrentSkill->ConsumeMP; // 해당 스킬 MP만큼 플레이어 MP 차감
		}
	}
}

void AMyBasicCharacter::SkillAttack1_Projectile_Create() // 스킬1 발동 시 나갈 발사체를 생성 후 발사
{
	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(0.0f, 0.0f, 90.f));
	UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		float temp = 0;

		for (int32 i = 0; i < 20; i++) // 45도 간격으로 모든 방향으로 발사체를 발사
		{
			temp = 18.f * i;

			FRotator TempSpawnRotation = SpawnRotation + FRotator(0.f, temp, 0.0f);
			ASkillAttack1_Projectile* Skill1Projectile = World->SpawnActor<ASkillAttack1_Projectile>(Skill1_Projectile, SpawnLocation, TempSpawnRotation);
			Skill1Projectile->ProjectileDamage = AttackPower * CharacterCurrentSkill->SkillPower;
			Skill1Projectile->MyPawn = this; // 발사체를 발사시키는 플레이어를 할당
		}
	}
}

void AMyBasicCharacter::SkillAttack2() // 스킬2 실행 함수
{
	SkillIndex = 2;
	CharacterCurrentSkill = CharacterSkillTable->FindRow<FCharacterSkill>(*FString::FromInt(SkillIndex), TEXT(""));

	if (bSkill2Possible == false) // 쿨타임이 완료되지 않은 상태에서는 실행X
		return;

	if (CharacterCurrentSkill != nullptr)
	{
		if (MyLevel < CharacterCurrentSkill->ActivationLevel || MyMP < CharacterCurrentSkill->ConsumeMP)
			return; // 플레이어 레벨이 스킬 활성화 레벨보다 낮을 시 OR 플레이어 MP가 부족할 시 -> 스킬을 실행하지 않음
	}

	if (bIsDuringAttack == false && bIsStarting == false) // 공격중이지 않을 때 && 레벨 시작 Anim이 진행중이지 않을 때
	{
		if (GetMovementComponent()->IsFalling() == false) // 공중에 있지 않을 때
		{
			bSkill2Possible = false;

			SkillIndex = 2;
			CharacterCurrentSkill = CharacterSkillTable->FindRow<FCharacterSkill>(*FString::FromInt(SkillIndex), TEXT(""));

			FTimerHandle TH_Skill2CoolTime;
			GetWorldTimerManager().SetTimer(TH_Skill2CoolTime, this, &AMyBasicCharacter::CoolTimeEnd, CharacterCurrentSkill->CoolTime, false);

			PlayAnimMontage(SkillAttack2_Anim); // 스킬 AnimMontage를 실행
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillAttack2_WarmUp_FX, GetCurrentWeapon()->GetActorLocation());
			// 원하는 지점에서 Particle 출력
			bIsDuringAttack = true; // 공격중인지 여부를 나타내는 변수에 true 할당
			MyMP -= CharacterCurrentSkill->ConsumeMP; // 해당 스킬 MP만큼 플레이어 MP 차감
		}
	}
}

void AMyBasicCharacter::SkillAttack2_Projectile_Create() // 스킬2 발동 시 나갈 발사체를 생성 후 발사
{
	FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(0.0f, 0.0f, 90.f));
	UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		float temp = 0;

		for (int32 i = 0; i < 20; i++) // 45도 간격으로 모든 방향으로 발사체를 발사
		{
			temp = 18.f * i;

			FRotator TempSpawnRotation = SpawnRotation + FRotator(0.f, temp, 0.0f);
			ASkillAttack1_Projectile* Skill2Projectile = World->SpawnActor<ASkillAttack1_Projectile>(Skill2_Projectile, SpawnLocation, TempSpawnRotation);
			Skill2Projectile->ProjectileDamage = AttackPower * CharacterCurrentSkill->SkillPower;
			Skill2Projectile->MyPawn = this; // 발사체를 발사시키는 플레이어를 할당
		}
	}
}

void AMyBasicCharacter::CoolTimeEnd() // 쿨타임이 있는 스킬2 사용 후 쿨타임 종료를 알리는 함수
{
	bSkill2Possible = true;
}





