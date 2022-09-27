// Fill out your copyright notice in the Description page of Project Settings.


#include "AController_StartMenu.h"
#include "BasicCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
// #include "UI_Inventory_Widget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "MyProject2GameMode.h"
#include "MyBasicCharacter.h"
#include "UI_Die_Widget.h"


AAController_StartMenu::AAController_StartMenu()
{
	
	isShowGameMenu = false; // 게임 메뉴창 열려있는지에 대한 여부 -> false 할당
	isShowInventory = false; // 게임 인벤토리창 열려있는지에 대한 여부 -> false 할당

	/*
	isShowShopMenu = false;
	*/

	// bShowMouseCursor = true;
	// bEnableClickEvents = true;
	// bEnableMouseOverEvents = true;

	/////////////////* 각 UIBPClass에 해당하는 위젯 불러오기 *//////////////////


	static ConstructorHelpers::FClassFinder<UUserWidget>obj(TEXT("/Game/Blueprints/UI/BP_GameHUD"));
	if (obj.Succeeded())
	{
		uiGameBPClass = obj.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> gamemenuUI(TEXT("/Game/Blueprints/UI/BP_GameMenu"));
	if (gamemenuUI.Succeeded())
	{
		uiGameMenuBPClass = gamemenuUI.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryUI(TEXT("/Game/Blueprints/UI/BP_ITemInventory"));
	if (InventoryUI.Succeeded())
	{
		uiInventoryBPClass = InventoryUI.Class;
	}

	/*
	static ConstructorHelpers::FClassFinder<UUserWidget> ItmeSlot(TEXT("/Game/Blueprints/UI/BP_ItemSlot"));
	if (ItmeSlot.Succeeded())
	{
		uiItemSlotBPClass = ItmeSlot.Class;
	}
	*/

	static ConstructorHelpers::FClassFinder<UUserWidget> LevelSelectUI(TEXT("/Game/Blueprints/UI/BP_Level_Select"));
	if (LevelSelectUI.Succeeded())
	{
		uiLevelSelectBPClass = LevelSelectUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> DieUI(TEXT("/Game/Blueprints/UI/BP_HUD_Die"));
	if (DieUI.Succeeded())
	{
		uiGameDieBPClass = DieUI.Class;
	}

		/*
	static ConstructorHelpers::FClassFinder<UUserWidget> ShopUI(TEXT("/Game/_My/UI/ShopUI_WidgetBP"));
	if (ShopUI.Succeeded())
	{
		uiGameShopBPClass = ShopUI.Class;
	}
	*/
}

void AAController_StartMenu::BeginPlay()
{
	Super::BeginPlay();

	/* 플레이어의 기본 게임 위젯을 화면에 띄어줌 */

	if (uiGameBPClass)
	{
		uiGameWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameBPClass);
		if (uiGameWidget)
		{
			uiGameWidget->AddToViewport();
		}
	}
}

void AAController_StartMenu::SetupInputComponent() // 버튼 <-> 함수 바인딩
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &AAController_StartMenu::ShowGameMenu); // 게임메뉴 오픈 버튼
	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AAController_StartMenu::ShowInventory); // 인벤토리 버튼
	InputComponent->BindAction("Attack", IE_Pressed, this, &AAController_StartMenu::WeaponAttack); // 공격 버튼
	InputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &AAController_StartMenu::ChangeWeapon); // 무기교체 버튼
	InputComponent->BindAction("ChangeMouseSetting", IE_Pressed, this, &AAController_StartMenu::ChangeMouseSetting); // 무기교체 버튼
}

void AAController_StartMenu::SetDungeonLev(int32 Value)
{
	DungeonLev = Value;
}

int32 AAController_StartMenu::GetDungeonLev()
{
	return DungeonLev;
}

void AAController_StartMenu::ChangeMouseSetting()
{
	bShowMouseCursor = !bShowMouseCursor;
	bEnableClickEvents = !bEnableClickEvents;
	bEnableMouseOverEvents = !bEnableMouseOverEvents;
}


void AAController_StartMenu::ShowGameMenu() // 게임 메뉴 오픈
{
	if (uiGameMenuBPClass && isShowGameMenu == false) // 게임메뉴 위젯이 있다면 & 게임 메뉴가 닫힌 상태라면
	{
		uiGameMenuWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameMenuBPClass);
		if (uiGameMenuWidget)
		{
			uiGameMenuWidget->AddToViewport(); // 화면에 게임메뉴 출력

			AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
			if (MyCharac)
			{
				MyCharac->PlaySound("UIOpen"); // 메뉴창 오픈 효과음 출력 
			}
		}

		isShowGameMenu = true; // 게임 메뉴 오픈 여부 -> true 할당
	}	
}

void AAController_StartMenu::CloseGameMenu() // 게임 메뉴 닫기
{
	uiGameMenuWidget->RemoveFromViewport();
	isShowGameMenu = false; // 게임 메뉴 오픈 여부 -> false 할당

	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	if (MyCharac)
	{
		MyCharac->PlaySound("UIClose"); // 메뉴창 닫기 효과음 출력 
	}
}

void AAController_StartMenu::ShowInventory() // 인벤토리 오픈
{
	if (uiInventoryBPClass && isShowInventory == false) // 인벤토리 위젯이 있다면 & 인벤토리가 닫힌 상태라면
	{
		uiInventoryWidget = CreateWidget<UUserWidget>(GetWorld(), uiInventoryBPClass);

		if (uiInventoryWidget)
		{
			uiInventoryWidget->AddToViewport(); // 화면에 인벤토리 출력
	
			AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
			if (MyCharac)
			{
				MyCharac->PlaySound("UIOpen"); // 인벤토리창 오픈 효과음 출력 
			}
		}

		isShowInventory = true; // 인벤토리 오픈 여부 -> true 할당
	}
}

void AAController_StartMenu::CloseInventory() // 인벤토리 닫기
{
	//uiInventoryWidget->RemoveFromViewport();
	uiInventoryWidget->RemoveFromParent();
	isShowInventory = false;

	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	if (MyCharac)
	{
		MyCharac->PlaySound("UIClose"); // 인벤토리창 닫기 효과음 출력 
	}
}



void AAController_StartMenu::WeaponAttack() // 공격 버튼 누를 시 호출
{
	ABasicCharacter* MyCharac = Cast<ABasicCharacter>(GetPawn());
	
	if (MyCharac)
	{
		MyCharac->Attack(); 
	}
}

void AAController_StartMenu::Skill1() // 스킬1 버튼 누를 시 호출
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->SkillAttack1();
	}
}

void AAController_StartMenu::Skill2() // 스킬2 버튼 누를 시 호출
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->SkillAttack2();
	}
}

void AAController_StartMenu::ChangeWeapon() // 무기교체 버튼 누를 시 호출
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->OnChangeWeapon();
	}
}


void AAController_StartMenu::ShowDieUI() // 플레이어가 죽었을 때 호출
{
	ABasicCharacter* MyCharac = Cast<ABasicCharacter>(GetPawn());

	if (uiGameDieBPClass)
	{
		uiGameDieWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameDieBPClass);

		if (uiGameDieWidget)
		{
			uiGameWidget->RemoveFromParent(); // 플레이어 기본 위젯을 닫음
			Cast<UUI_Die_Widget>(uiGameDieWidget)->Player = MyCharac;
			uiGameDieWidget->AddToViewport(); // 죽었을 때의 위젯을 화면에 출력


			// DIe 위젯 배경음악 출력
			UUI_Die_Widget* Temp_uiGameDieWidget = Cast<UUI_Die_Widget>(uiGameDieWidget);
			if (Temp_uiGameDieWidget != nullptr) 
				UGameplayStatics::SpawnSoundAttached(Temp_uiGameDieWidget->BGMSound, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
			
			/* 마우스 버튼을 보이게 해줌 */

			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
		}
	}
	
}

void AAController_StartMenu::UseConsumableItem(int32 ConsumableItemIndex)  // 소비 아이템 사용
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->MyCurrentItem = MyCharac->MyItemDataTable->FindRow<FItem>(*FString::FromInt(ConsumableItemIndex), TEXT(""));

		if (MyCharac->MyCurrentItem == nullptr || MyCharac->MyCurrentItem->ItemCnt == 0)
			return;

		MyCharac->MyCurrentItem->ItemCnt -= 1;

		if (MyCharac->MyCurrentItem->ItemName == "HP Potion") // HP 포션
		{
			if (MyCharac->Get_Health() + 100.f <= MyCharac->Get_MaxHealth())
			{
				MyCharac->Set_Health(MyCharac->Get_Health() + 100.f); // 체력에 100을 더해줌
			}
			else
			{
				MyCharac->Set_Health(MyCharac->Get_MaxHealth()); // 체력을 최대값으로 할당
			}

			MyCharac->PlaySound("UsePotion"); // 포션 사용 효과음 재생
		}
		else if (MyCharac->MyCurrentItem->ItemName == "MP Potion") // MP 포션
		{
			if (MyCharac->Get_MP() + 50.f < MyCharac->Get_MaxMP())
			{
				MyCharac->Set_MP(MyCharac->Get_MP() + 50.f); // MP에 50을 더해줌
			}
			else
			{
				MyCharac->Set_MP(MyCharac->Get_MaxMP()); // MP를 최대값으로 할당
			}

			MyCharac->PlaySound("UsePotion"); // 포션 사용 효과음 재생
		}

		MyCharac->SaveCharacterStat(); // 아이템 사용 후 데이터 저장
	}
}


/*
void AAController_StartMenu::ShowShopUI()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ShowShopUI");
	isShowShopMenu = true;

	//if (uiGameShopBPClass)
	//{
	//	uiGameDieWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameShopBPClass);
	//	if (uiGameShopWidget)
	//	{
	//		//uiGameWidget->RemoveFromParent();
	//		uiGameShopWidget->AddToViewport();

	//		bShowMouseCursor = true;
	//		bEnableClickEvents = true;
	//		bEnableMouseOverEvents = true;
	//	}
	//}


}

void AAController_StartMenu::CloseShopUI()
{
	isShowShopMenu = false;
}

void AAController_StartMenu::CreateItemSlots()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;


	//Show ItemSlots
	//UUI_Inventory_Widget* MyInvenWidgetClass = Cast<UUI_Inventory_Widget>(GetWorld());
	//
	//UUI_Inventory_Widget* MyInvenPanel = Cast<UUI_Inventory_Widget>(GetWorld());
	//auto s = MyInvenPanel->GridPanel_ItemSlots;
	//
	//for (int i = 0; i < 8; i++)
	//{
	//	//MyInvenWidgetClass->GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);
	//	uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
	//	s->AddChildToGrid(uiItemSlotWidget);
	//	//uiItemSlotWidget->AddToViewport();
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, __FUNCTION__);
	//}
}
*/
