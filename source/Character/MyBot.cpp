// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBot.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AISense_Sight.h"
#include "Engine/World.h"

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "HPBar.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"

AMyBot::AMyBot()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 입력된 방향키 방향을 향하게 해줌
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; // 캐릭터 최고 속도

	setup_stimulus();// AI 구현에 따른 자극을 주는 함수


	/* 봇의 스탯을 연동하는 데이터 테이블 */
	BotStatTable = CreateDefaultSubobject<UDataTable>(TEXT("BotStatTable"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyBotStat_Obj(TEXT("/Game/Data/MyBotStat_DataTable"));
	if (MyBotStat_Obj.Succeeded())
	{
		BotStatTable = MyBotStat_Obj.Object;
	}

	MyCharacterName = "Bot";

	if (Widget_Component != nullptr) // HP 위젯 출력
	{
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget>widget_class(TEXT("/Game/Blueprints/UI/HPBar"));

		if (widget_class.Succeeded())
		{
			Widget_Component->SetWidgetClass(widget_class.Class);

		}
	}
}

void AMyBot::BeginPlay()
{
	Super::BeginPlay();

	SetBotStat(MyLevel); // 봇의 스텟 초기화
	PlaySound("Start"); // 나타날 때의 효과음생 재생
}

void AMyBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* 위젯에 표시할 캐릭터 HP 정보 실시간 연동*/
	MyHPNum = (MyHealth / MyMaxHealth);

	auto const uw = Cast<UHPBar>(Widget_Component->GetUserWidgetObject());
	if (uw)
	{
		// HP/MaxHP 값을 Widget의 ProgressBar 수치에 할당
		uw->set_bar_value_percent(MyHPNum);
		uw->set_Level_TextBlock(MyLevel);
	}
}

void AMyBot::SetBotStat(int32 NewLevel)
{
	BotCurrentStat = BotStatTable->FindRow<FBotStat>(*FString::FromInt(NewLevel), TEXT(""));

	if (BotCurrentStat != nullptr)
	{
		AttackPower = BotCurrentStat->BotAttack; // 공격력

		MyMaxHealth = BotCurrentStat->BotMaxHP; //1000.0f; // HP 최댓값 
		MyHealth = MyMaxHealth; // HP 초기값 할당

		DropEXP = BotCurrentStat->BotDropExp; // 10000.0f; // 봇이 죽을 시 플레이어가 얻게 될 경험치
	}
}

int AMyBot::melee_attack_Implementation() // 공격 Anim 실행
{
	if (bIsDuringHitAnim == true)
		return 0;

	if (Attack_Anim)
	{
		PlayAnimMontage(Attack_Anim);

		// ThrowBomb();
	}
	return 0;
}

void AMyBot::ThrowBomb() // 폭탄 던지기 수행 -> AnimNotifyState에서 지정한 지점에서 호출
{
	if (bIsDuringHitAnim == true)
		return;

	if (MyBotName == "Bomb" && MyBomb != nullptr)
	{
		const FRotator SpawnRotation = GetActorRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(50.f, 6.f, 90.f));
		UWorld* const World = GetWorld();

		if (World != nullptr)
		{
			AMyProjectile* Bomb = World->SpawnActor<AMyProjectile>(MyBomb, SpawnLocation, SpawnRotation);

			if (Bomb)
				Bomb->ProjectileDamage = AttackPower; // 폭탄 공격력에 몬스터 공격력 할당
		}
	}
}

UAnimMontage* AMyBot::get_montage()
{
	return Attack_Anim;
}

void AMyBot::setup_stimulus() // AI 구현에 따른 자극을 주는 함수
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

void AMyBot::PostInitializeComponents() // 무기를 캐릭터에 붙여줄 함수
{
	Super::PostInitializeComponents();
	SpawndefaultInventory(); // 인벤토리에 있는 무기를 불러와줌
}

void AMyBot::PlaySound(FString SoundName) // 효과음 재생 함수
{
	if (BotSoundMap.Find(SoundName) != nullptr)
		UGameplayStatics::SpawnSoundAttached(BotSoundMap[SoundName], RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
}

