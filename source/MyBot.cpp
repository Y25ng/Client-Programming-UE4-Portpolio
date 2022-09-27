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
	GetCharacterMovement()->bOrientRotationToMovement = true; // ĳ���Ͱ� �Էµ� ����Ű ������ ���ϰ� ����
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; // ĳ���� �ְ� �ӵ�

	setup_stimulus();// AI ������ ���� �ڱ��� �ִ� �Լ�


	/* ���� ������ �����ϴ� ������ ���̺� */
	BotStatTable = CreateDefaultSubobject<UDataTable>(TEXT("BotStatTable"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyBotStat_Obj(TEXT("/Game/Data/MyBotStat_DataTable"));
	if (MyBotStat_Obj.Succeeded())
	{
		BotStatTable = MyBotStat_Obj.Object;
	}

	MyCharacterName = "Bot";

	if (Widget_Component != nullptr) // HP ���� ���
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

	SetBotStat(MyLevel); // ���� ���� �ʱ�ȭ
	PlaySound("Start"); // ��Ÿ�� ���� ȿ������ ���
}

void AMyBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* ������ ǥ���� ĳ���� HP ���� �ǽð� ����*/
	MyHPNum = (MyHealth / MyMaxHealth);

	auto const uw = Cast<UHPBar>(Widget_Component->GetUserWidgetObject());
	if (uw)
	{
		// HP/MaxHP ���� Widget�� ProgressBar ��ġ�� �Ҵ�
		uw->set_bar_value_percent(MyHPNum);
		uw->set_Level_TextBlock(MyLevel);
	}
}

void AMyBot::SetBotStat(int32 NewLevel)
{
	BotCurrentStat = BotStatTable->FindRow<FBotStat>(*FString::FromInt(NewLevel), TEXT(""));

	if (BotCurrentStat != nullptr)
	{
		AttackPower = BotCurrentStat->BotAttack; // ���ݷ�

		MyMaxHealth = BotCurrentStat->BotMaxHP; //1000.0f; // HP �ִ� 
		MyHealth = MyMaxHealth; // HP �ʱⰪ �Ҵ�

		DropEXP = BotCurrentStat->BotDropExp; // 10000.0f; // ���� ���� �� �÷��̾ ��� �� ����ġ
	}
}

int AMyBot::melee_attack_Implementation() // ���� Anim ����
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

void AMyBot::ThrowBomb() // ��ź ������ ���� -> AnimNotifyState���� ������ �������� ȣ��
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
				Bomb->ProjectileDamage = AttackPower; // ��ź ���ݷ¿� ���� ���ݷ� �Ҵ�
		}
	}
}

UAnimMontage* AMyBot::get_montage()
{
	return Attack_Anim;
}

void AMyBot::setup_stimulus() // AI ������ ���� �ڱ��� �ִ� �Լ�
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

void AMyBot::PostInitializeComponents() // ���⸦ ĳ���Ϳ� �ٿ��� �Լ�
{
	Super::PostInitializeComponents();
	SpawndefaultInventory(); // �κ��丮�� �ִ� ���⸦ �ҷ�����
}

void AMyBot::PlaySound(FString SoundName) // ȿ���� ��� �Լ�
{
	if (BotSoundMap.Find(SoundName) != nullptr)
		UGameplayStatics::SpawnSoundAttached(BotSoundMap[SoundName], RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
}

