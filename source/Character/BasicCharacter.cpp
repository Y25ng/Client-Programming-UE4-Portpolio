// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicCharacter.h"

#include "MyBasicCharacter.h"
#include "MyBoss.h"
#include "MyWeapon.h"
#include "SkillAttack1_Projectile.h"
#include "Components/CapsuleComponent.h"// 캡슐 충돌체를 위한 라이브러리
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "HPBar.h"
#include "GameHUD_UI.h"
#include "AController_StartMenu.h"
#include "UI_DungeonReward_Widget.h"
#include "UI_CharacterName_Widget.h"

// GetCharacterMovement()를 사용하기 위함
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsDuringAttack = false; // 공격중인지 여부 초기값
	bIsDuringHitAnim = false; // Hit Anim이 실행중인지 여부

	ComboAttack_Num = 0; // 기본 공격 콤보 수 초기값
	MyLevel = 1; // 레벨 초기값
	DungeonLevel = 0; // 던전 레벨 초기값

	DungeonMonsterCnt.Add(24); // 1단계 몬스터 수
	DungeonMonsterCnt.Add(24); // 2단계 몬스터 수
	PlayerKillCnt = 0; // 던전에서 죽인 몬스터 수 
	bAllMonsterDie = false; // 던전에서 보스를 제외한 모든 몬스터를 죽였는지에 대한 여부

	SaveSlotName = "Player1"; // 캐릭터 스텟 저장 슬롯 이름

	///////////////////////////////////* 데이터 테이블 연동*////////////////////////////////////////

	CharacterStatTable = CreateDefaultSubobject<UDataTable>(TEXT("CharacterStatTable")); // 캐릭터 스텟 데이터 테이블의 기반 구조체 객체 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> MyCharacterStat_Obj(TEXT("/Game/Data/MyCharacterStat_DataTableD"));
	if (MyCharacterStat_Obj.Succeeded())
	{
		CharacterStatTable = MyCharacterStat_Obj.Object; 
	}
	// SetCharacterStat(); // 데이터 테이블 연동을 통한 캐릭터 스텟 세팅

	CharacterSkillTable = CreateDefaultSubobject<UDataTable>(TEXT("CharacterSkillTable")); // 캐릭터 스킬 데이터 테이블의 기반 구조체 객체 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> MyCharacterSkill_Obj(TEXT("/Game/Data/MyCharacterSkill_DataTable"));
	if (MyCharacterSkill_Obj.Succeeded())
	{
		CharacterSkillTable = MyCharacterSkill_Obj.Object;
	}

	MyItemDataTable = CreateDefaultSubobject<UDataTable>(TEXT("MyItemDataTable")); // 캐릭터 아이템 데이터 테이블의 기반 구조체 객체 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> MyItemDataTable_Obj(TEXT("/Game/Data/MyCharacterItem_DataTable"));
	if (MyItemDataTable_Obj.Succeeded())
	{
		MyItemDataTable = MyItemDataTable_Obj.Object;
	}

	DungeonDataTable = CreateDefaultSubobject<UDataTable>(TEXT("Dungeon DataTable")); // 던전 데이터 테이블의 기반 구조체 객체 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> DungeonDataTable_Obj(TEXT("/Game/Data/MyDungeon_DataTable"));
	if (DungeonDataTable_Obj.Succeeded())
	{
		DungeonDataTable = DungeonDataTable_Obj.Object;
	}

	////////////////////////////////////////////* *////////////////////////////////////////////////////

	MyHPNum_String = FString::SanitizeFloat(MyHealth) + "/" + FString::SanitizeFloat(MyMaxHealth); // 위젯에 표시할 HP 정보
	MyMPNum_String = FString::SanitizeFloat(MyMP) + "/" + FString::SanitizeFloat(MyMaxMP); // 위젯에 표시할 MP 정보
	MyEXPNum_String = FString::SanitizeFloat(MyEXP) + "/" + FString::SanitizeFloat(MyMaxEXP); // 위젯에 표시할 EXP 정보

	bJumpAttack = false; // 점프 공격이 수행 되었는지에 대한 여부 할당

	Widget_Component = CreateDefaultSubobject <UWidgetComponent>(TEXT("HealthValue")); // HP 위젯 컴포넌트 객체 생성

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
	StartAnim(); // 캐릭터가 등장할 때마다 StartAnim 실행
}

void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* 위젯에 표시할 캐릭터 HP 정보 실시간 연동*/
	MyHPNum = (MyHealth / MyMaxHealth);
	MyHPNum_String = FString::SanitizeFloat(MyHealth) + " / " + FString::SanitizeFloat(MyMaxHealth);

	/* 위젯에 표시할 캐릭터 MP 정보 실시간 연동*/
	MyMPNum = (MyMP / MyMaxMP);
	MyMPNum_String = FString::SanitizeFloat(MyMP) + " / " + FString::SanitizeFloat(MyMaxMP);

	/* 위젯에 표시할 캐릭터 EXP 정보 실시간 연동*/
	MyEXPNum = (MyEXP / MyMaxEXP);
	MyEXPNum_String = FString::SanitizeFloat(MyEXP) + " / " + FString::SanitizeFloat(MyMaxEXP);

	auto const gameHUD = Cast<UGameHUD_UI>(Widget_Component->GetUserWidgetObject());
	if (MyCharacterName == "Player")
	{
		if (gameHUD)
		{
			// MP/MaxMP 값을 Widget의 ProgressBar 수치에 할당
			gameHUD->set_HUDbar_value_percent(MyHPNum, MyMPNum, MyEXPNum);
		}
	}
}

void ABasicCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) // 키 바인딩
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABasicCharacter::Attack);
}


///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////* 캐릭터 스텟 데이터 관련 함수 *///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::SaveCharacterStat() // 플레이어 정보 저장 함수
{
	// 현재 플레이어 정보를 저장할 객체 생성
	UMySaveGame* NewPlayerData = NewObject<UMySaveGame>(); 
	// NewPlayerData->PlayerName

	//////* 위에서 생성한 객체에 플레이어 현재 정보 할당 *////////

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

	// 플레이어 정보 저장
	UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0);
}

void ABasicCharacter::SetCharacterStat() // 데이터 테이블 연동을 통한 캐릭터 스텟 세팅
{
	if (MyCharacterName != "Player") // 플레이어가 아닐 시 실행X
		return ;

	//////////////////////* 캐릭터 스텟 불러오기 *///////////////////////////////

	// 저장된 플레이어 스텟 불러오기 -> 저장된 정보가 없다면 새로 생성
	auto MySaveGameData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (MySaveGameData == nullptr)
	{
		MySaveGameData = GetMutableDefault<UMySaveGame>();

		// 캐릭터 닉네임을 입력하는 UI 출력
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

	// 저장된 플레이어 레벨 불러오기
	MyLevel = MySaveGameData->Level;
	DungeonLevel = MySaveGameData->DungeonLevel; // 던전 레벨 불러오기
	NickName = MySaveGameData->PlayerName; // 캐릭터 닉네임 할당

	// 저장된 플레이어 레벨에 따른 체력, MP, 공격력 등을 데이터 테이블을 통해 불러오기
	CharacterCurrentStat = CharacterStatTable->FindRow<FCharacterStat>(*FString::FromInt(MyLevel), TEXT(""));

	// 던전 별 클리어 여부 불러오기
	for (int i = 0; i < MySaveGameData->DungeonClear.Num(); i++)
	{
		CurrentDungeon = DungeonDataTable->FindRow<FDungeonClearReward>(*FString::FromInt(i+1), TEXT(""));
		CurrentDungeon->bDungeonClear = MySaveGameData->DungeonClear[i];
	}

	// 레벨에 해당하는 스텟들을 플레이어 스텟에 할당
	if (CharacterCurrentStat != nullptr)
	{
		AttackPower = CharacterCurrentStat->Attack; // 공격력

		MyMaxHealth = CharacterCurrentStat->MaxHP; //1000.0f; // HP 최댓값 
		MyHealth = MyMaxHealth; // HP 초기값 할당

		MyMaxMP = CharacterCurrentStat->MaxMP; // 500.f; // MP 최댓값
		MyMP = MyMaxMP; // MP 초기값 할당

		MyMaxEXP = CharacterCurrentStat->NextExp; // 10000.0f; // EXP 최댓값
		MyEXP = MySaveGameData->Exp; // EXP 초기값 할당

		MyGold = MySaveGameData->Gold; // 골드
	}

	// 플레이어 소유 아이템 정보를 불러와서 할당
	for (int32 i = 1; i <= 2; i++)
	{
		MyCurrentItem = MyItemDataTable->FindRow<FItem>(*FString::FromInt(i), TEXT(""));
		MyCurrentItem->ItemCnt = MySaveGameData->ItemCntMap[MyCurrentItem->ItemName];
	}

	// 플레이어 정보 저장
	UGameplayStatics::SaveGameToSlot(MySaveGameData, SaveSlotName, 0);
}

void ABasicCharacter::LevelUpUpdate() // 레벨업에 따른 스텟 업데이트
{
	if(LevelUpFX != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LevelUpFX, GetActorLocation()); // 레벨업 Particle 효과 화면에 출력

	MyLevel += 1; // 레벨 1 증가

	CharacterCurrentStat = CharacterStatTable->FindRow<FCharacterStat>(*FString::FromInt(MyLevel), TEXT(""));
	// 해당 레벨에 해당하는 스텟 불러오기

	if (CharacterCurrentStat != nullptr)
	{
		AttackPower = CharacterCurrentStat->Attack; // 공격력

		MyMaxHealth = CharacterCurrentStat->MaxHP; //1000.0f; // HP 최댓값 
		MyHealth = MyMaxHealth; // HP 초기값 할당

		MyMaxMP = CharacterCurrentStat->MaxMP; // 500.f; // MP 최댓값
		MyMP = MyMaxMP; // MP 초기값 할당

		MyMaxEXP = CharacterCurrentStat->NextExp; // 10000.0f; // EXP 최댓값
		MyEXP = 0.0f; // EXP 초기값 할당
	}

	SaveCharacterStat(); // 플레이어 정보 저장
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* 프로퍼티 *////////////////////////////////////////
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

FName ABasicCharacter::GetMyCharacterName() // Pawn 종류 반환
{
	return MyCharacterName;
}

FName ABasicCharacter::GetWeaponAttachPoint() const // 무기를 장착할 소켓 이름 반환
{
	return WeaponAttachPoint;
}

AMyWeapon* ABasicCharacter::GetCurrentWeapon() // 현재 무기 반환
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

USkeletalMeshComponent* ABasicCharacter::GetSpecificPawnMesh() const // 캐릭터 스켈레탈 메쉬 반환
{
	return GetMesh();
}

TArray<class AMyWeapon*> ABasicCharacter::GetWeaponInventory()
{
	return Inventory;
}

void ABasicCharacter::SetbIsDuringAttack(bool Value) // 공격중인지 여부 할당
{
	bIsDuringAttack = Value;
}

bool ABasicCharacter::GetbIsDuringAttack() // 공격중인지 여부 반환
{
	return bIsDuringAttack;
}

void ABasicCharacter::SetComboAttack_Num(int32 Value) // 콤보 어택수 할당
{
	ComboAttack_Num = Value;
}

int32 ABasicCharacter::GetComboAttack_Num() // 콤보 어택 수 반환
{
	return ComboAttack_Num;
}

// TArray<UAnimMontage*> ABasicCharacter::GetAttack_Anim_Arr()
// {
	// return Attack_Anim_Arr;
// }

bool ABasicCharacter::GetbFinalAttack() // 마지막 콤보 공격인지 여부 반환
{
	return bFinalAttack;
}

void ABasicCharacter::SetbFinalAttack(bool Value) // 마지막 콤보 공격인지 여부 할당
{
	bFinalAttack = Value;
}

void ABasicCharacter::SetbDamagePossible(bool Value) // 데미지를 줄 수 있는지 여부 할당
{
	bDamagePossible = Value;
}

bool ABasicCharacter::GetbDamagePossible() // 데미지를 줄 수 있는지 여부 반환
{
	return bDamagePossible;
}

bool ABasicCharacter::GetbIsStarting() // 레벨 시작 Anim이 진행중인지 여부 반환
{
	return bIsStarting;
}

void ABasicCharacter::SetbIsStarting(bool Value)
{
	bIsStarting = Value;
}

float ABasicCharacter::Get_Health() const // 체력 반환
{
	return MyHealth;
}

float ABasicCharacter::Get_MaxHealth() const // 최대 체력 반환
{
	return MyMaxHealth;
}

void ABasicCharacter::Set_Health(float Value) // 체력 할당
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

bool ABasicCharacter::GetbIsDuringHitAnim() // Hit Anim이 진행중인지 반환
{
	return bIsDuringHitAnim;
}

void ABasicCharacter::SetbIsDuringHitAnim(bool Value) // Hit Anim이 진행중인지 할당
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
/////////////////////////////* 공격 관련 함수 *////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::Attack() // 공격 함수 
{
	if (bIsDuringAttack == false && bIsStarting == false) 
		// 공격중이지 않을 때 && 레벨 시작 Anim이 진행중이지 않을 때
	{
		if (GetMovementComponent()->IsFalling() == false) // 공중에 있지 않을 때 기본 콤보 공격 수행
		{
			PlayAnimMontage(CurrentWeapon->Attack_Anim_Arr[ComboAttack_Num]); // 무기에 저장된 공격 Anim 실행

			/*

				무기에 저장된 공격 Anim이 하나인 경우 -> 공격 Anim을 실행 후 함수 종료
				무기에 저장된 공격 Anim이 두개 이상   -> 콤보 수에 해당하는 공격 Anim을 실행 후 콤보 수를 +1
													  -> 다음 공격 땐 무기에 저장된 다음 인덱스의 공격 Anim 실행

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
		else if(bJumpAttack == false) // 공중에 있을 때 & 공중 공격을 아직 하지 않은 상태
		{
			bJumpAttack = true; // 공중 공격을 수행한 상태로 바꿔줌 
			bIsDuringAttack = true; // 공격중인 상태로 만들어줌
			PlayAnimMontage(CurrentWeapon->JumpAttack_Anim); // 점프 공격 수행
		}
	}
}

void ABasicCharacter::AttackEnd() // 공격 종료 함수
{
	bIsDuringAttack = false; // 공격 여부 false 할당
}


///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* 시작 Anim 관련 함수 *///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::StartAnim() // 시작 애니메이션 실행 
{
	if (LevelStart_Anim)
	{
		bIsStarting = true;
		float StartingTime = PlayAnimMontage(LevelStart_Anim); // 캐릭터 시작or등장 시 시작 Anim 실행

		FTimerHandle TH_StartingAnim;
		GetWorldTimerManager().SetTimer(TH_StartingAnim, this, &ABasicCharacter::StartAnimEnd, StartingTime, false); // 시작 Anim이 끝났음을 해당 변수에 할당해줌
	}
}

void ABasicCharacter::StartAnimEnd() // 시작 애니메이션 종료
{
	bIsStarting = false;
}


///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* 무기 관련 함수 *////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::SpawndefaultInventory() // 캐릭터에 저장된 무기들을 인벤토리에 저장 & 캐릭터에 첫 번째 무기를 장착 
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num(); // 캐릭터에 저장된 무기 갯수

	for (int32 i = 0; i < NumWeaponClasses; i++) // 캐릭터에 저장된 무기들을 인벤토리에 추가해줌
	{
		if (DefaultInventoryClasses[i] != nullptr)
		{
			FActorSpawnParameters SpawnInfo;
			UWorld* WRLD = GetWorld();
			AMyWeapon* NewWeapon = WRLD->SpawnActor<AMyWeapon>(DefaultInventoryClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	if (Inventory.Num() > 0) // 인벤토리에 저장된 무기가 1개 이상인 경우 첫 번째 무기를 캐릭터에 장착 시켜줌
	{
		EquipWeapon(Inventory[0]);

		if (Inventory.Num() > 1) // 장착하고 남은 나머지 무기들은 숨겨줌
		{
			for (int i = 1; i < Inventory.Num(); i++)
			{
				Inventory[i]->GetWeaponMesh()->SetHiddenInGame(true);
			}
		}
	}
}

void ABasicCharacter::AddWeapon(AMyWeapon* Weapon) // 무기 인벤토리에 추가 함수
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon); // 중복 무기가 추가 되지 않게 넣어줌
	}
}

void ABasicCharacter::EquipWeapon(AMyWeapon* Weapon) // 무기 장착을 위한 함수
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ABasicCharacter::SetCurrentWeapon(AMyWeapon* NewWeapon, AMyWeapon* LastWeapon) // 현재 무기를 설정할 함수
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

	if (LocalLastWeapon) // 새로운 무기 이전 무기를 장착 해제
	{
		LocalLastWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon; // 새로운 무기 할당

	if (NewWeapon) // 새로운 무기를 장착
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
		CurrentWeapon = NewWeapon;
	}
}

void ABasicCharacter::OnChangeWeapon() // 무기 교체 함수 -> 인벤토리 다음 인덱스의 무기로 현재 무기를 교체
{
	const int32 CurrentWeaponIndex = Inventory.IndexOfByKey(CurrentWeapon);

	AMyWeapon* NextWeapon = Inventory[(CurrentWeaponIndex + 1) % Inventory.Num()]; //

	EquipWeapon(NextWeapon);
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////* 데미지 관련 함수 *////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void ABasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent,
	APawn* PawnInstigator, AActor* DamageCauser) // 데미지를 받을 때 호출
{
	if (MyCharacterName == "Bot") // 몬스터의 경우 피격을 당하면 Anim을 중지 후 피격 Anin을 실행
	{
		AMyBoss* TempBoss = Cast<AMyBoss>(this);
		if (TempBoss != nullptr && TempBoss->GetbDuringSkill() == true)
			return ; // 보스인 경우 && 보스가 궁극기를 실행중인 경우 -> 피격 애니메이션을 실행하지 않음

		StopAnimMontage();
		AttackEnd();
		PlayAnimMontage(BeHit_Anim); // Hit Anim 실행
	}
	else if (MyCharacterName == "Player") // 플레이어의 경우 공격중이 아닐 때만 피격 Anim을 실행
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
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser); // 데미지를 적용
	}
}


float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, 
	AController* EventInstigator, AActor* DamageCauser) // 데미지를 반환
{
	const float MyGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser); // 받은 데미지


	if (MyHealth <= 0.0f || MyGetDamage <= 0.0f)
	{
		return 0.0f; // 체력이 0 이하거나 받은 데미지가 0 이하인 경우 
	}
	else
	{
		MyHealth -= MyGetDamage; // 받은 데미지 만큼 빼줌
	}


	if (MyHealth <= 0.0f) // 데미지 적용 이후 -> 데미지가 0 이하가 됐을 때 
	{
		PlayAnimMontage(Death_Anim); // Death 애니메이션 실행

		if (MyCharacterName == "Player") // 플레이어의 경우 죽은 후 화면을 보여줌
		{
			SaveCharacterStat();
			DeathAnimEnd();
			CurrentWeapon->OnUnEquip();
			AAController_StartMenu* con = Cast<AAController_StartMenu>(GetOwner());
			con->ShowDieUI();

			AMyBasicCharacter* tempPlayer = Cast<AMyBasicCharacter>(this);
			tempPlayer->PlaySound("Die"); // 플레이어 죽음 효과음 재생

		}
		else if(MyCharacterName == "Bot")
		{
			AMyBoss* Boss = Cast<AMyBoss>(this);
			if (Boss) // 보스인 경우 해당 던전 레벨에 해당하는 보상 지급
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

				// 해당 던전 클리어 여부에 true 할당
				player->CurrentDungeon = player->DungeonDataTable->FindRow<FDungeonClearReward>(*FString::FromInt(player->GetDungeonLevel()), TEXT(""));
				player->CurrentDungeon->bDungeonClear = true;

				// 해당 던전 클리어에 따른 보상 지급
				player->Set_Exp(player->Get_Exp() + player->CurrentDungeon->RewardExp);
				player->SetMyGold(player->GetMyGold() + player->CurrentDungeon->RewardGold);

				// 보상 지급 내용과 로비로 돌아가는 버튼이 담긴 UI 출력
				if (player->uiDungeonRewardBPClass)
				{
					player->uiDungeonRewardWidget = CreateWidget<UUserWidget>(GetWorld(), player->uiDungeonRewardBPClass);
					if (player->uiDungeonRewardWidget)
					{
						Cast<UUI_DungeonReward_Widget>(player->uiDungeonRewardWidget)->Player = player;
						player->uiDungeonRewardWidget->AddToViewport();
						player->PlaySound("DungeonClear"); // 던전 클리어 효과음 출력
					}
				}
			}

			AMyBot* MyBot = Cast<AMyBot>(this);
			MyBot->PlaySound("Die"); // 몬스터 죽음 효과음 재생

			// 몬스터의 경우 Die 함수 실행
			Die(MyGetDamage, DamageEvent, EventInstigator, DamageCauser); 
		}
		
	}
	else // 데미지 적용 이후 체력이 0 보다 클 때
	{
		//if(this->IsA(AMyBasicCharacter::StaticClass()))
		/*
		if(MyCharacterName == "Player")
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Be attacked")));
			*/

		OnHit(MyGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : nullptr, DamageCauser);
	}

	return MyGetDamage; // 받은 데미지 반환
}

void ABasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, 
	AController* Killer, AActor* DamageCauser) // 죽음 함수
{
	if (CurrentWeapon)
		CurrentWeapon->Destroy(); // 무기가 있다면 없애줌

	MyHealth = FMath::Min(0.0f, MyHealth); // 체력값 0 할당

	UDamageType const* const DamageType = DamageEvent. DamageTypeClass ? Cast <const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();
	Killer = GetDamageInstigator(Killer, *DamageType);
	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent()) // 충돌체 해제
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement()) // 움직임 조종 해제
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller != nullptr) // Controller 해제
	{
		Controller->UnPossess();
	}

	DeathAnimEnd(); // 캐릭터 삭제 함수


	// 죽은 Pawn이 몬스터고 죽인 Pawn이 Player라면 Player에게 경험치를 더해줌
	if(DamageCauser->IsA(AMyWeapon::StaticClass()))
	{
		AMyWeapon* weapon = Cast<AMyWeapon>(DamageCauser);
		AMyBasicCharacter* player = Cast<AMyBasicCharacter>(weapon->GetMyPawn());
		
		if (player != nullptr && player->MyCharacterName == "Player")
		{
			player->MyEXP += DropEXP; 
			player->SaveCharacterStat();

			player->PlayerKillCnt += 1; // 죽인 몬스터 수 1 증가

			int32 tempMonsterCnt = player->DungeonMonsterCnt[player->DungeonLevel - 1];
			if (tempMonsterCnt == player->PlayerKillCnt)
				player->bAllMonsterDie = true;
			// 모든 몬스터가 죽었음을 할당
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

			player->PlayerKillCnt += 1; // 죽인 몬스터 수 1 증가

			int32 tempMonsterCnt = player->DungeonMonsterCnt[player->DungeonLevel - 1];
			if (tempMonsterCnt == player->PlayerKillCnt)
				player->bAllMonsterDie = true;
			// 모든 몬스터가 죽었음을 할당
		}
	}
}

void ABasicCharacter::DeathAnimEnd() // 죽은 이후 캐릭터를 지워주는 함수
{
	// this->SetActorHiddenInGame(true); // 캐릭터를 숨김
	SetLifeSpan(2.0f); // 캐릭터를 2초 후 지워줌
}






