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
	
	isShowGameMenu = false; // ���� �޴�â �����ִ����� ���� ���� -> false �Ҵ�
	isShowInventory = false; // ���� �κ��丮â �����ִ����� ���� ���� -> false �Ҵ�

	/*
	isShowShopMenu = false;
	*/

	// bShowMouseCursor = true;
	// bEnableClickEvents = true;
	// bEnableMouseOverEvents = true;

	/////////////////* �� UIBPClass�� �ش��ϴ� ���� �ҷ����� *//////////////////


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

	/* �÷��̾��� �⺻ ���� ������ ȭ�鿡 ����� */

	if (uiGameBPClass)
	{
		uiGameWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameBPClass);
		if (uiGameWidget)
		{
			uiGameWidget->AddToViewport();
		}
	}
}

void AAController_StartMenu::SetupInputComponent() // ��ư <-> �Լ� ���ε�
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &AAController_StartMenu::ShowGameMenu); // ���Ӹ޴� ���� ��ư
	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AAController_StartMenu::ShowInventory); // �κ��丮 ��ư
	InputComponent->BindAction("Attack", IE_Pressed, this, &AAController_StartMenu::WeaponAttack); // ���� ��ư
	InputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &AAController_StartMenu::ChangeWeapon); // ���ⱳü ��ư
	InputComponent->BindAction("ChangeMouseSetting", IE_Pressed, this, &AAController_StartMenu::ChangeMouseSetting); // ���ⱳü ��ư
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


void AAController_StartMenu::ShowGameMenu() // ���� �޴� ����
{
	if (uiGameMenuBPClass && isShowGameMenu == false) // ���Ӹ޴� ������ �ִٸ� & ���� �޴��� ���� ���¶��
	{
		uiGameMenuWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameMenuBPClass);
		if (uiGameMenuWidget)
		{
			uiGameMenuWidget->AddToViewport(); // ȭ�鿡 ���Ӹ޴� ���

			AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
			if (MyCharac)
			{
				MyCharac->PlaySound("UIOpen"); // �޴�â ���� ȿ���� ��� 
			}
		}

		isShowGameMenu = true; // ���� �޴� ���� ���� -> true �Ҵ�
	}	
}

void AAController_StartMenu::CloseGameMenu() // ���� �޴� �ݱ�
{
	uiGameMenuWidget->RemoveFromViewport();
	isShowGameMenu = false; // ���� �޴� ���� ���� -> false �Ҵ�

	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	if (MyCharac)
	{
		MyCharac->PlaySound("UIClose"); // �޴�â �ݱ� ȿ���� ��� 
	}
}

void AAController_StartMenu::ShowInventory() // �κ��丮 ����
{
	if (uiInventoryBPClass && isShowInventory == false) // �κ��丮 ������ �ִٸ� & �κ��丮�� ���� ���¶��
	{
		uiInventoryWidget = CreateWidget<UUserWidget>(GetWorld(), uiInventoryBPClass);

		if (uiInventoryWidget)
		{
			uiInventoryWidget->AddToViewport(); // ȭ�鿡 �κ��丮 ���
	
			AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
			if (MyCharac)
			{
				MyCharac->PlaySound("UIOpen"); // �κ��丮â ���� ȿ���� ��� 
			}
		}

		isShowInventory = true; // �κ��丮 ���� ���� -> true �Ҵ�
	}
}

void AAController_StartMenu::CloseInventory() // �κ��丮 �ݱ�
{
	//uiInventoryWidget->RemoveFromViewport();
	uiInventoryWidget->RemoveFromParent();
	isShowInventory = false;

	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	if (MyCharac)
	{
		MyCharac->PlaySound("UIClose"); // �κ��丮â �ݱ� ȿ���� ��� 
	}
}



void AAController_StartMenu::WeaponAttack() // ���� ��ư ���� �� ȣ��
{
	ABasicCharacter* MyCharac = Cast<ABasicCharacter>(GetPawn());
	
	if (MyCharac)
	{
		MyCharac->Attack(); 
	}
}

void AAController_StartMenu::Skill1() // ��ų1 ��ư ���� �� ȣ��
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->SkillAttack1();
	}
}

void AAController_StartMenu::Skill2() // ��ų2 ��ư ���� �� ȣ��
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->SkillAttack2();
	}
}

void AAController_StartMenu::ChangeWeapon() // ���ⱳü ��ư ���� �� ȣ��
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->OnChangeWeapon();
	}
}


void AAController_StartMenu::ShowDieUI() // �÷��̾ �׾��� �� ȣ��
{
	ABasicCharacter* MyCharac = Cast<ABasicCharacter>(GetPawn());

	if (uiGameDieBPClass)
	{
		uiGameDieWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameDieBPClass);

		if (uiGameDieWidget)
		{
			uiGameWidget->RemoveFromParent(); // �÷��̾� �⺻ ������ ����
			Cast<UUI_Die_Widget>(uiGameDieWidget)->Player = MyCharac;
			uiGameDieWidget->AddToViewport(); // �׾��� ���� ������ ȭ�鿡 ���


			// DIe ���� ������� ���
			UUI_Die_Widget* Temp_uiGameDieWidget = Cast<UUI_Die_Widget>(uiGameDieWidget);
			if (Temp_uiGameDieWidget != nullptr) 
				UGameplayStatics::SpawnSoundAttached(Temp_uiGameDieWidget->BGMSound, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
			
			/* ���콺 ��ư�� ���̰� ���� */

			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
		}
	}
	
}

void AAController_StartMenu::UseConsumableItem(int32 ConsumableItemIndex)  // �Һ� ������ ���
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());

	if (MyCharac)
	{
		MyCharac->MyCurrentItem = MyCharac->MyItemDataTable->FindRow<FItem>(*FString::FromInt(ConsumableItemIndex), TEXT(""));

		if (MyCharac->MyCurrentItem == nullptr || MyCharac->MyCurrentItem->ItemCnt == 0)
			return;

		MyCharac->MyCurrentItem->ItemCnt -= 1;

		if (MyCharac->MyCurrentItem->ItemName == "HP Potion") // HP ����
		{
			if (MyCharac->Get_Health() + 100.f <= MyCharac->Get_MaxHealth())
			{
				MyCharac->Set_Health(MyCharac->Get_Health() + 100.f); // ü�¿� 100�� ������
			}
			else
			{
				MyCharac->Set_Health(MyCharac->Get_MaxHealth()); // ü���� �ִ밪���� �Ҵ�
			}

			MyCharac->PlaySound("UsePotion"); // ���� ��� ȿ���� ���
		}
		else if (MyCharac->MyCurrentItem->ItemName == "MP Potion") // MP ����
		{
			if (MyCharac->Get_MP() + 50.f < MyCharac->Get_MaxMP())
			{
				MyCharac->Set_MP(MyCharac->Get_MP() + 50.f); // MP�� 50�� ������
			}
			else
			{
				MyCharac->Set_MP(MyCharac->Get_MaxMP()); // MP�� �ִ밪���� �Ҵ�
			}

			MyCharac->PlaySound("UsePotion"); // ���� ��� ȿ���� ���
		}

		MyCharac->SaveCharacterStat(); // ������ ��� �� ������ ����
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
