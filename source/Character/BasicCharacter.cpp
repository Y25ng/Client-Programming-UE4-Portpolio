// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicCharacter.h"

#include "MyBasicCharacter.h"
#include "MyBoss.h"
#include "MyWeapon.h"
#include "SkillAttack1_Projectile.h"
#include "Components/CapsuleComponent.h"// ĸ�� �浹ü�� ���� ���̺귯��
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "HPBar.h"
#include "GameHUD_UI.h"
#include "AController_StartMenu.h"
#include "UI_DungeonReward_Widget.h"
#include "UI_CharacterName_Widget.h"

// GetCharacterMovement()�� ����ϱ� ����
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsDuringAttack = false; // ���������� ���� �ʱⰪ
	bIsDuringHitAnim = false; // Hit Anim�� ���������� ����

	ComboAttack_Num = 0; // �⺻ ���� �޺� �� �ʱⰪ
	MyLevel = 1; // ���� �ʱⰪ
	DungeonLevel = 0; // ���� ���� �ʱⰪ

	DungeonMonsterCnt.Add(24); // 1�ܰ� ���� ��
	DungeonMonsterCnt.Add(24); // 2�ܰ� ���� ��
	PlayerKillCnt = 0; // �������� ���� ���� �� 
	bAllMonsterDie = false; // �������� ������ ������ ��� ���͸� �׿������� ���� ����

	SaveSlotName = "Player1"; // ĳ���� ���� ���� ���� �̸�

	///////////////////////////////////* ������ ���̺� ����*////////////////////////////////////////

	CharacterStatTable = CreateDefaultSubobject<UDataTable>(TEXT("CharacterStatTable")); // ĳ���� ���� ������ ���̺��� ��� ����ü ��ü ����
	static ConstructorHelpers::FObjectFinder<UDataTable> MyCharacterStat_Obj(TEXT("/Game/Data/MyCharacterStat_DataTableD"));
	if (MyCharacterStat_Obj.Succeeded())
	{
		CharacterStatTable = MyCharacterStat_Obj.Object; 
	}
	// SetCharacterStat(); // ������ ���̺� ������ ���� ĳ���� ���� ����

	CharacterSkillTable = CreateDefaultSubobject<UDataTable>(TEXT("CharacterSkillTable")); // ĳ���� ��ų ������ ���̺��� ��� ����ü ��ü ����
	static ConstructorHelpers::FObjectFinder<UDataTable> MyCharacterSkill_Obj(TEXT("/Game/Data/MyCharacterSkill_DataTable"));
	if (MyCharacterSkill_Obj.Succeeded())
	{
		CharacterSkillTable = MyCharacterSkill_Obj.Object;
	}

	MyItemDataTable = CreateDefaultSubobject<UDataTable>(TEXT("MyItemDataTable")); // ĳ���� ������ ������ ���̺��� ��� ����ü ��ü ����
	static ConstructorHelpers::FObjectFinder<UDataTable> MyItemDataTable_Obj(TEXT("/Game/Data/MyCharacterItem_DataTable"));
	if (MyItemDataTable_Obj.Succeeded())
	{
		MyItemDataTable = MyItemDataTable_Obj.Object;
	}

	DungeonDataTable = CreateDefaultSubobject<UDataTable>(TEXT("Dungeon DataTable")); // ���� ������ ���̺��� ��� ����ü ��ü ����
	static ConstructorHelpers::FObjectFinder<UDataTable> DungeonDataTable_Obj(TEXT("/Game/Data/MyDungeon_DataTable"));
	if (DungeonDataTable_Obj.Succeeded())
	{
		DungeonDataTable = DungeonDataTable_Obj.Object;
	}

	////////////////////////////////////////////* *////////////////////////////////////////////////////

	MyHPNum_String = FString::SanitizeFloat(MyHealth) + "/" + FString::SanitizeFloat(MyMaxHealth); // ������ ǥ���� HP ����
	MyMPNum_String = FString::SanitizeFloat(MyMP) + "/" + FString::SanitizeFloat(MyMaxMP); // ������ ǥ���� MP ����
	MyEXPNum_String = FString::SanitizeFloat(MyEXP) + "/" + FString::SanitizeFloat(MyMaxEXP); // ������ ǥ���� EXP ����

	bJumpAttack = false; // ���� ������ ���� �Ǿ������� ���� ���� �Ҵ�

	Widget_Component = CreateDefaultSubobject <UWidgetComponent>(TEXT("HealthValue")); // HP ���� ������Ʈ ��ü ����

	static ConstructorHelpers::FClassFinder<UUserWidget> DungeonRewardUI(TEXT("/Game/Blueprints/UI/BP_DungeonLevel_Reward"));
	if (DungeonRewardUI.Succeeded())
	{
		uiDungeonRewardBPClass = DungeonRewardUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> CharacterNameUI(TEXT("/Game/Blueprints/UI/BP_CharacterName"));
	if (CharacterNameUI.Succeeded())
	{
		uiCharacterNameBPClass = CharacterNameUI.Class;
	}
}

void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterStat();
	StartAnim(); // ĳ���Ͱ� ������ ������ StartAnim ����
}

void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* ������ ǥ���� ĳ���� HP ���� �ǽð� ����*/
	MyHPNum = (MyHealth / MyMaxHealth);
	MyHPNum_String = FString::SanitizeFloat(MyHealth) + " / " + FString::SanitizeFloat(MyMaxHealth);

	/* ������ ǥ���� ĳ���� MP ���� �ǽð� ����*/
	MyMPNum = (MyMP / MyMaxMP);
	MyMPNum_String = FString::SanitizeFloat(MyMP) + " / " + FString::SanitizeFloat(MyMaxMP);

	/* ������ ǥ���� ĳ���� EXP ���� �ǽð� ����*/
	MyEXPNum = (MyEXP / MyMaxEXP);
	MyEXPNum_String = FString::SanitizeFloat(MyEXP) + " / " + FString::SanitizeFloat(MyMaxEXP);

	auto const gameHUD = Cast<UGameHUD_UI>(Widget_Component->GetUserWidgetObject());
	if (MyCharacterName == "Player")
	{
		if (gameHUD)
		{
			// MP/MaxMP ���� Widget�� ProgressBar ��ġ�� �Ҵ�
			gameHUD->set_HUDbar_value_percent(MyHPNum, MyMPNum, MyEXPNum);
		}
	}
}

void ABasicCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) // Ű ���ε�
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABasicCharacter::Attack);
}


///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////* ĳ���� ���� ������ ���� �Լ� *///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::SaveCharacterStat() // �÷��̾� ���� ���� �Լ�
{
	// ���� �÷��̾� ������ ������ ��ü ����
	UMySaveGame* NewPlayerData = NewObject<UMySaveGame>(); 
	// NewPlayerData->PlayerName

	//////* ������ ������ ��ü�� �÷��̾� ���� ���� �Ҵ� *////////

	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	NewPlayerData->Level = MyLevel;
	NewPlayerData->Exp = MyEXP;
	NewPlayerData->DungeonLevel = DungeonLevel;
	NewPlayerData->Gold = MyGold;
	NewPlayerData->PlayerName = NickName;
	
	for (int32 i = 1; i <= 2; i++)
	{
		MyCurrentItem = MyItemDataTable->FindRow<FItem>(*FString::FromInt(i), TEXT(""));
		NewPlayerData->ItemCntMap[MyCurrentItem->ItemName] = MyCurrentItem->ItemCnt;
	}

	for (int i = 0; i < NewPlayerData->DungeonClear.Num(); i++)
	{
		CurrentDungeon = DungeonDataTable->FindRow<FDungeonClearReward>(*FString::FromInt(i + 1), TEXT(""));
		NewPlayerData->DungeonClear[i] = CurrentDungeon->bDungeonClear;
	}

	// �÷��̾� ���� ����
	UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0);
}

void ABasicCharacter::SetCharacterStat() // ������ ���̺� ������ ���� ĳ���� ���� ����
{
	if (MyCharacterName != "Player") // �÷��̾ �ƴ� �� ����X
		return ;

	//////////////////////* ĳ���� ���� �ҷ����� *///////////////////////////////

	// ����� �÷��̾� ���� �ҷ����� -> ����� ������ ���ٸ� ���� ����
	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (MySaveGameData == nullptr)
	{
		MySaveGameData = GetMutableDefault<UMySaveGame>();

		// ĳ���� �г����� �Է��ϴ� UI ���
		if (uiCharacterNameBPClass)
		{
			uiCharacterNameWidget = CreateWidget<UUserWidget>(GetWorld(), uiCharacterNameBPClass);
			if (uiCharacterNameWidget)
			{
				Cast<UUI_CharacterName_Widget>(uiCharacterNameWidget)->Player = this;
				uiCharacterNameWidget->AddToViewport();
			}
		}
	}

	// ����� �÷��̾� ���� �ҷ�����
	MyLevel = MySaveGameData->Level;
	DungeonLevel = MySaveGameData->DungeonLevel; // ���� ���� �ҷ�����
	NickName = MySaveGameData->PlayerName; // ĳ���� �г��� �Ҵ�

	// ����� �÷��̾� ������ ���� ü��, MP, ���ݷ� ���� ������ ���̺��� ���� �ҷ�����
	CharacterCurrentStat = CharacterStatTable->FindRow<FCharacterStat>(*FString::FromInt(MyLevel), TEXT(""));

	// ���� �� Ŭ���� ���� �ҷ�����
	for (int i = 0; i < MySaveGameData->DungeonClear.Num(); i++)
	{
		CurrentDungeon = DungeonDataTable->FindRow<FDungeonClearReward>(*FString::FromInt(i+1), TEXT(""));
		CurrentDungeon->bDungeonClear = MySaveGameData->DungeonClear[i];
	}

	// ������ �ش��ϴ� ���ݵ��� �÷��̾� ���ݿ� �Ҵ�
	if (CharacterCurrentStat != nullptr)
	{
		AttackPower = CharacterCurrentStat->Attack; // ���ݷ�

		MyMaxHealth = CharacterCurrentStat->MaxHP; //1000.0f; // HP �ִ� 
		MyHealth = MyMaxHealth; // HP �ʱⰪ �Ҵ�

		MyMaxMP = CharacterCurrentStat->MaxMP; // 500.f; // MP �ִ�
		MyMP = MyMaxMP; // MP �ʱⰪ �Ҵ�

		MyMaxEXP = CharacterCurrentStat->NextExp; // 10000.0f; // EXP �ִ�
		MyEXP = MySaveGameData->Exp; // EXP �ʱⰪ �Ҵ�

		MyGold = MySaveGameData->Gold; // ���
	}

	// �÷��̾� ���� ������ ������ �ҷ��ͼ� �Ҵ�
	for (int32 i = 1; i <= 2; i++)
	{
		MyCurrentItem = MyItemDataTable->FindRow<FItem>(*FString::FromInt(i), TEXT(""));
		MyCurrentItem->ItemCnt = MySaveGameData->ItemCntMap[MyCurrentItem->ItemName];
	}

	// �÷��̾� ���� ����
	UGameplayStatics::SaveGameToSlot(MySaveGameData, SaveSlotName, 0);
}

void ABasicCharacter::LevelUpUpdate() // �������� ���� ���� ������Ʈ
{
	if(LevelUpFX != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LevelUpFX, GetActorLocation()); // ������ Particle ȿ�� ȭ�鿡 ���

	MyLevel += 1; // ���� 1 ����

	CharacterCurrentStat = CharacterStatTable->FindRow<FCharacterStat>(*FString::FromInt(MyLevel), TEXT(""));
	// �ش� ������ �ش��ϴ� ���� �ҷ�����

	if (CharacterCurrentStat != nullptr)
	{
		AttackPower = CharacterCurrentStat->Attack; // ���ݷ�

		MyMaxHealth = CharacterCurrentStat->MaxHP; //1000.0f; // HP �ִ� 
		MyHealth = MyMaxHealth; // HP �ʱⰪ �Ҵ�

		MyMaxMP = CharacterCurrentStat->MaxMP; // 500.f; // MP �ִ�
		MyMP = MyMaxMP; // MP �ʱⰪ �Ҵ�

		MyMaxEXP = CharacterCurrentStat->NextExp; // 10000.0f; // EXP �ִ�
		MyEXP = 0.0f; // EXP �ʱⰪ �Ҵ�
	}

	SaveCharacterStat(); // �÷��̾� ���� ����
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* ������Ƽ *////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


int32 ABasicCharacter::GetDungeonLevel()
{
	return DungeonLevel;
}

void ABasicCharacter::SetDungeonLevel(int32 Value)
{
	DungeonLevel = Value;
}

bool ABasicCharacter::GetbAllMonsterDie()
{
	return bAllMonsterDie;
}

FString ABasicCharacter::GetNickName()
{
	return NickName;
}

void ABasicCharacter::SetNickName(FString Value)
{
	NickName = Value;
}

FName ABasicCharacter::GetMyCharacterName() // Pawn ���� ��ȯ
{
	return MyCharacterName;
}

FName ABasicCharacter::GetWeaponAttachPoint() const // ���⸦ ������ ���� �̸� ��ȯ
{
	return WeaponAttachPoint;
}

AMyWeapon* ABasicCharacter::GetCurrentWeapon() // ���� ���� ��ȯ
{
	return CurrentWeapon;
}

FString ABasicCharacter::GetSaveSlotName()
{
	return SaveSlotName;
}

int32 ABasicCharacter::GetMyGold()
{
	return MyGold;
}

void ABasicCharacter::SetMyGold(int32 Value)
{
	MyGold = Value;
}

USkeletalMeshComponent* ABasicCharacter::GetSpecificPawnMesh() const // ĳ���� ���̷�Ż �޽� ��ȯ
{
	return GetMesh();
}

TArray<class AMyWeapon*> ABasicCharacter::GetWeaponInventory()
{
	return Inventory;
}

void ABasicCharacter::SetbIsDuringAttack(bool Value) // ���������� ���� �Ҵ�
{
	bIsDuringAttack = Value;
}

bool ABasicCharacter::GetbIsDuringAttack() // ���������� ���� ��ȯ
{
	return bIsDuringAttack;
}

void ABasicCharacter::SetComboAttack_Num(int32 Value) // �޺� ���ü� �Ҵ�
{
	ComboAttack_Num = Value;
}

int32 ABasicCharacter::GetComboAttack_Num() // �޺� ���� �� ��ȯ
{
	return ComboAttack_Num;
}

// TArray<UAnimMontage*> ABasicCharacter::GetAttack_Anim_Arr()
// {
	// return Attack_Anim_Arr;
// }

bool ABasicCharacter::GetbFinalAttack() // ������ �޺� �������� ���� ��ȯ
{
	return bFinalAttack;
}

void ABasicCharacter::SetbFinalAttack(bool Value) // ������ �޺� �������� ���� �Ҵ�
{
	bFinalAttack = Value;
}

void ABasicCharacter::SetbDamagePossible(bool Value) // �������� �� �� �ִ��� ���� �Ҵ�
{
	bDamagePossible = Value;
}

bool ABasicCharacter::GetbDamagePossible() // �������� �� �� �ִ��� ���� ��ȯ
{
	return bDamagePossible;
}

bool ABasicCharacter::GetbIsStarting() // ���� ���� Anim�� ���������� ���� ��ȯ
{
	return bIsStarting;
}

void ABasicCharacter::SetbIsStarting(bool Value)
{
	bIsStarting = Value;
}

float ABasicCharacter::Get_Health() const // ü�� ��ȯ
{
	return MyHealth;
}

float ABasicCharacter::Get_MaxHealth() const // �ִ� ü�� ��ȯ
{
	return MyMaxHealth;
}

void ABasicCharacter::Set_Health(float Value) // ü�� �Ҵ�
{
	MyHealth = Value;
}

float ABasicCharacter::Get_MP() const
{
	return MyMP;
}

void ABasicCharacter::Set_MP(float Value)
{
	MyMP = Value;
}

float ABasicCharacter::Get_MaxMP()
{
	return MyMaxMP;
}

float ABasicCharacter::Get_Exp() const
{
	return MyEXP;
}

void ABasicCharacter::Set_Exp(float Value)
{
	MyEXP = Value;
}

float ABasicCharacter::Get_AttackPower()
{
	return AttackPower;
}

bool ABasicCharacter::GetbIsDuringHitAnim() // Hit Anim�� ���������� ��ȯ
{
	return bIsDuringHitAnim;
}

void ABasicCharacter::SetbIsDuringHitAnim(bool Value) // Hit Anim�� ���������� �Ҵ�
{
	bIsDuringHitAnim = Value;
}

bool ABasicCharacter::GetbIsDuringJumpEnd()
{
	return bIsDuringJumpEnd;
}

void ABasicCharacter::SetbIsDuringJumpEnd(bool Value)
{
	bIsDuringJumpEnd = Value;
}

void ABasicCharacter::SetbJumpAttack(bool Value)
{
	bJumpAttack = Value;
}

UAnimMontage* ABasicCharacter::GetLevelStart_Anim()
{
	return  LevelStart_Anim;
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* ���� ���� �Լ� *////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::Attack() // ���� �Լ� 
{
	if (bIsDuringAttack == false && bIsStarting == false) 
		// ���������� ���� �� && ���� ���� Anim�� ���������� ���� ��
	{
		if (GetMovementComponent()->IsFalling() == false) // ���߿� ���� ���� �� �⺻ �޺� ���� ����
		{
			PlayAnimMontage(CurrentWeapon->Attack_Anim_Arr[ComboAttack_Num]); // ���⿡ ����� ���� Anim ����

			/*

				���⿡ ����� ���� Anim�� �ϳ��� ��� -> ���� Anim�� ���� �� �Լ� ����
				���⿡ ����� ���� Anim�� �ΰ� �̻�   -> �޺� ���� �ش��ϴ� ���� Anim�� ���� �� �޺� ���� +1
													  -> ���� ���� �� ���⿡ ����� ���� �ε����� ���� Anim ����

			*/

			if (CurrentWeapon->Attack_Anim_Arr.Num() == 1)
				return;
			else if (ComboAttack_Num == CurrentWeapon->Attack_Anim_Arr.Num() - 1)
				bFinalAttack = true;
			else
				bFinalAttack = false;

			bIsDuringAttack = true;

			if (bIsDuringAttack == true)
				ComboAttack_Num = (ComboAttack_Num + 1) % CurrentWeapon->Attack_Anim_Arr.Num();
		}
		else if(bJumpAttack == false) // ���߿� ���� �� & ���� ������ ���� ���� ���� ����
		{
			bJumpAttack = true; // ���� ������ ������ ���·� �ٲ��� 
			bIsDuringAttack = true; // �������� ���·� �������
			PlayAnimMontage(CurrentWeapon->JumpAttack_Anim); // ���� ���� ����
		}
	}
}

void ABasicCharacter::AttackEnd() // ���� ���� �Լ�
{
	bIsDuringAttack = false; // ���� ���� false �Ҵ�
}


///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* ���� Anim ���� �Լ� *///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::StartAnim() // ���� �ִϸ��̼� ���� 
{
	if (LevelStart_Anim)
	{
		bIsStarting = true;
		float StartingTime = PlayAnimMontage(LevelStart_Anim); // ĳ���� ����or���� �� ���� Anim ����

		FTimerHandle TH_StartingAnim;
		GetWorldTimerManager().SetTimer(TH_StartingAnim, this, &ABasicCharacter::StartAnimEnd, StartingTime, false); // ���� Anim�� �������� �ش� ������ �Ҵ�����
	}
}

void ABasicCharacter::StartAnimEnd() // ���� �ִϸ��̼� ����
{
	bIsStarting = false;
}


///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* ���� ���� �Լ� *////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::SpawndefaultInventory() // ĳ���Ϳ� ����� ������� �κ��丮�� ���� & ĳ���Ϳ� ù ��° ���⸦ ���� 
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num(); // ĳ���Ϳ� ����� ���� ����

	for (int32 i = 0; i < NumWeaponClasses; i++) // ĳ���Ϳ� ����� ������� �κ��丮�� �߰�����
	{
		if (DefaultInventoryClasses[i] != nullptr)
		{
			FActorSpawnParameters SpawnInfo;
			UWorld* WRLD = GetWorld();
			AMyWeapon* NewWeapon = WRLD->SpawnActor<AMyWeapon>(DefaultInventoryClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	if (Inventory.Num() > 0) // �κ��丮�� ����� ���Ⱑ 1�� �̻��� ��� ù ��° ���⸦ ĳ���Ϳ� ���� ������
	{
		EquipWeapon(Inventory[0]);

		if (Inventory.Num() > 1) // �����ϰ� ���� ������ ������� ������
		{
			for (int i = 1; i < Inventory.Num(); i++)
			{
				Inventory[i]->GetWeaponMesh()->SetHiddenInGame(true);
			}
		}
	}
}

void ABasicCharacter::AddWeapon(AMyWeapon* Weapon) // ���� �κ��丮�� �߰� �Լ�
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon); // �ߺ� ���Ⱑ �߰� ���� �ʰ� �־���
	}
}

void ABasicCharacter::EquipWeapon(AMyWeapon* Weapon) // ���� ������ ���� �Լ�
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ABasicCharacter::SetCurrentWeapon(AMyWeapon* NewWeapon, AMyWeapon* LastWeapon) // ���� ���⸦ ������ �Լ�
{
	AMyWeapon* LocalLastWeapon = nullptr;

	if (LastWeapon != nullptr)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon)
	{
		LocalLastWeapon = CurrentWeapon;
	}

	if (LocalLastWeapon) // ���ο� ���� ���� ���⸦ ���� ����
	{
		LocalLastWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon; // ���ο� ���� �Ҵ�

	if (NewWeapon) // ���ο� ���⸦ ����
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
		CurrentWeapon = NewWeapon;
	}
}

void ABasicCharacter::OnChangeWeapon() // ���� ��ü �Լ� -> �κ��丮 ���� �ε����� ����� ���� ���⸦ ��ü
{
	const int32 CurrentWeaponIndex = Inventory.IndexOfByKey(CurrentWeapon);

	AMyWeapon* NextWeapon = Inventory[(CurrentWeaponIndex + 1) % Inventory.Num()]; //

	EquipWeapon(NextWeapon);
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* ������ ���� �Լ� *////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent,
	APawn* PawnInstigator, AActor* DamageCauser) // �������� ���� �� ȣ��
{
	if (MyCharacterName == "Bot") // ������ ��� �ǰ��� ���ϸ� Anim�� ���� �� �ǰ� Anin�� ����
	{
		AMyBoss* TempBoss = Cast<AMyBoss>(this);
		if (TempBoss != nullptr && TempBoss->GetbDuringSkill() == true)
			return ; // ������ ��� && ������ �ñر⸦ �������� ��� -> �ǰ� �ִϸ��̼��� �������� ����

		StopAnimMontage();
		AttackEnd();
		PlayAnimMontage(BeHit_Anim); // Hit Anim ����
	}
	else if (MyCharacterName == "Player") // �÷��̾��� ��� �������� �ƴ� ���� �ǰ� Anim�� ����
	{
		if (bIsDuringAttack == false)
		{
			StopAnimMontage();
			AttackEnd();
			PlayAnimMontage(BeHit_Anim);
		}
	}

	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser); // �������� ����
	}
}


float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, 
	AController* EventInstigator, AActor* DamageCauser) // �������� ��ȯ
{
	const float MyGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser); // ���� ������


	if (MyHealth <= 0.0f || MyGetDamage <= 0.0f)
	{
		return 0.0f; // ü���� 0 ���ϰų� ���� �������� 0 ������ ��� 
	}
	else
	{
		MyHealth -= MyGetDamage; // ���� ������ ��ŭ ����
	}


	if (MyHealth <= 0.0f) // ������ ���� ���� -> �������� 0 ���ϰ� ���� �� 
	{
		PlayAnimMontage(Death_Anim); // Death �ִϸ��̼� ����

		if (MyCharacterName == "Player") // �÷��̾��� ��� ���� �� ȭ���� ������
		{
			SaveCharacterStat();
			DeathAnimEnd();
			CurrentWeapon->OnUnEquip();
			AAController_StartMenu* con = Cast<AAController_StartMenu>(GetOwner());
			con->ShowDieUI();

			AMyBasicCharacter* tempPlayer = Cast<AMyBasicCharacter>(this);
			tempPlayer->PlaySound("Die"); // �÷��̾� ���� ȿ���� ���

		}
		else if(MyCharacterName == "Bot")
		{
			AMyBoss* Boss = Cast<AMyBoss>(this);
			if (Boss) // ������ ��� �ش� ���� ������ �ش��ϴ� ���� ����
			{
				AMyBasicCharacter* player = nullptr;
				AMyWeapon* weapon = Cast<AMyWeapon>(DamageCauser);

				if(weapon)
					player = Cast<AMyBasicCharacter>(weapon->GetMyPawn());

				if (player == nullptr)
				{
					ASkillAttack1_Projectile* PlayerProjectile = Cast<ASkillAttack1_Projectile>(DamageCauser);
					
					if (PlayerProjectile)
						player = Cast<AMyBasicCharacter>(PlayerProjectile->MyPawn);
				}

				// �ش� ���� Ŭ���� ���ο� true �Ҵ�
				player->CurrentDungeon = player->DungeonDataTable->FindRow<FDungeonClearReward>(*FString::FromInt(player->GetDungeonLevel()), TEXT(""));
				player->CurrentDungeon->bDungeonClear = true;

				// �ش� ���� Ŭ��� ���� ���� ����
				player->Set_Exp(player->Get_Exp() + player->CurrentDungeon->RewardExp);
				player->SetMyGold(player->GetMyGold() + player->CurrentDungeon->RewardGold);

				// ���� ���� ����� �κ�� ���ư��� ��ư�� ��� UI ���
				if (player->uiDungeonRewardBPClass)
				{
					player->uiDungeonRewardWidget = CreateWidget<UUserWidget>(GetWorld(), player->uiDungeonRewardBPClass);
					if (player->uiDungeonRewardWidget)
					{
						Cast<UUI_DungeonReward_Widget>(player->uiDungeonRewardWidget)->Player = player;
						player->uiDungeonRewardWidget->AddToViewport();
						player->PlaySound("DungeonClear"); // ���� Ŭ���� ȿ���� ���
					}
				}
			}

			AMyBot* MyBot = Cast<AMyBot>(this);
			MyBot->PlaySound("Die"); // ���� ���� ȿ���� ���

			// ������ ��� Die �Լ� ����
			Die(MyGetDamage, DamageEvent, EventInstigator, DamageCauser); 
		}
		
	}
	else // ������ ���� ���� ü���� 0 ���� Ŭ ��
	{
		//if(this->IsA(AMyBasicCharacter::StaticClass()))
		/*
		if(MyCharacterName == "Player")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Be attacked")));
			*/

		OnHit(MyGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : nullptr, DamageCauser);
	}

	return MyGetDamage; // ���� ������ ��ȯ
}

void ABasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, 
	AController* Killer, AActor* DamageCauser) // ���� �Լ�
{
	if (CurrentWeapon)
		CurrentWeapon->Destroy(); // ���Ⱑ �ִٸ� ������

	MyHealth = FMath::Min(0.0f, MyHealth); // ü�°� 0 �Ҵ�

	UDamageType const* const DamageType = DamageEvent. DamageTypeClass ? Cast <const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();
	Killer = GetDamageInstigator(Killer, *DamageType);
	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent()) // �浹ü ����
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement()) // ������ ���� ����
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller != nullptr) // Controller ����
	{
		Controller->UnPossess();
	}

	DeathAnimEnd(); // ĳ���� ���� �Լ�


	// ���� Pawn�� ���Ͱ� ���� Pawn�� Player��� Player���� ����ġ�� ������
	if(DamageCauser->IsA(AMyWeapon::StaticClass()))
	{
		AMyWeapon* weapon = Cast<AMyWeapon>(DamageCauser);
		AMyBasicCharacter* player = Cast<AMyBasicCharacter>(weapon->GetMyPawn());
		
		if (player != nullptr && player->MyCharacterName == "Player")
		{
			player->MyEXP += DropEXP; 
			player->SaveCharacterStat();

			player->PlayerKillCnt += 1; // ���� ���� �� 1 ����

			int32 tempMonsterCnt = player->DungeonMonsterCnt[player->DungeonLevel - 1];
			if (tempMonsterCnt == player->PlayerKillCnt)
				player->bAllMonsterDie = true;
			// ��� ���Ͱ� �׾����� �Ҵ�
		}
	}
	else if (DamageCauser->IsA(ASkillAttack1_Projectile::StaticClass()))
	{
		ASkillAttack1_Projectile* SkillProjectile = Cast<ASkillAttack1_Projectile>(DamageCauser);
		AMyBasicCharacter* player = Cast<AMyBasicCharacter>(SkillProjectile->MyPawn);

		if (player != nullptr && player->MyCharacterName == "Player")
		{
			player->MyEXP += DropEXP;
			player->SaveCharacterStat();

			player->PlayerKillCnt += 1; // ���� ���� �� 1 ����

			int32 tempMonsterCnt = player->DungeonMonsterCnt[player->DungeonLevel - 1];
			if (tempMonsterCnt == player->PlayerKillCnt)
				player->bAllMonsterDie = true;
			// ��� ���Ͱ� �׾����� �Ҵ�
		}
	}
}

void ABasicCharacter::DeathAnimEnd() // ���� ���� ĳ���͸� �����ִ� �Լ�
{
	// this->SetActorHiddenInGame(true); // ĳ���͸� ����
	SetLifeSpan(2.0f); // ĳ���͸� 2�� �� ������
}






