// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory_Widget.h"

#include "AController_StartMenu.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/UniformGridSlot.h"
#include "Components/HorizontalBox.h"
#include "Engine.h"
#include "MyBasicCharacter.h"
// #include "UI_ItemSlot_Widget.h"

void UUI_Inventory_Widget::NativeConstruct()
{

	if (Btn_Inventory_Close) 
	{
		Btn_Inventory_Close->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_CloseWindow);
		// 인벤토리 닫기 버튼 누를 시 해당 함수 호출
	}
	if (Btn_ConsumableItem_1)
	{
		Btn_ConsumableItem_1->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_1);
		// 인벤토리 소비 아이템 목록1 사용 시 호출
	}
	if (Btn_ConsumableItem_2)
	{
		Btn_ConsumableItem_2->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_2);
		// 인벤토리 소비 아이템 목록2 사용 시 호출
	}
	if (Btn_ConsumableItem_3)
	{
		Btn_ConsumableItem_3->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_3);
		// 인벤토리 소비 아이템 목록2 사용 시 호출
	}
	if (Btn_ConsumableItem_4)
	{
		Btn_ConsumableItem_4->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_4);
		// 인벤토리 소비 아이템 목록2 사용 시 호출
	}
	//SpawnSlots();
	if (Btn_Weapon1)
	{
		Btn_Weapon1->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon1_OnEquip);
	}
	if (Btn_Weapon2)
	{
		Btn_Weapon2->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon2_OnEquip);
	}
	if (Btn_Weapon3)
	{
		Btn_Weapon3->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon3_OnEquip);
	}
	if (Btn_Weapon4)
	{
		Btn_Weapon4->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Weapon4_OnEquip);
	}
}


void UUI_Inventory_Widget::Btn_Inventory_CloseWindow() // 인벤토리 닫기 버튼 누를 시 호출되는 함수
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->CloseInventory();
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_1() // 인벤토리 소비 아이템 사용 함수
{
	Use_ConsumableItem(1);
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_2() // 인벤토리 소비 아이템 사용 함수
{
	Use_ConsumableItem(2);
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_3() // 인벤토리 소비 아이템 사용 함수
{
	Use_ConsumableItem(3);
}

void UUI_Inventory_Widget::Btn_Inventory_Use_ConsumableItem_4() // 인벤토리 소비 아이템 사용 함수
{
	Use_ConsumableItem(4);
}

void UUI_Inventory_Widget::Use_ConsumableItem(int32 Index)
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	contoller->UseConsumableItem(Index);
}

void UUI_Inventory_Widget::Btn_Weapon1_OnEquip()
{
	WeaponChange(0);
}

void UUI_Inventory_Widget::Btn_Weapon2_OnEquip()
{
	WeaponChange(1);
}

void UUI_Inventory_Widget::Btn_Weapon3_OnEquip()
{
	WeaponChange(2);
}

void UUI_Inventory_Widget::Btn_Weapon4_OnEquip()
{
	WeaponChange(3);
}

void UUI_Inventory_Widget::WeaponChange(int32 index)
{
	AAController_StartMenu* contoller = Cast<AAController_StartMenu>(GetOwningPlayer());
	ABasicCharacter* MyCharac = Cast<ABasicCharacter>(contoller->GetPawn());

	if (MyCharac->GetWeaponInventory().Num() - 1 < index) // 해당 슬롯에 무기가 없을 경우 아무 동작 X
		return;

	if (MyCharac->GetCurrentWeapon() == (MyCharac->GetWeaponInventory())[index]) // 현재 장착중인 무기를 선택할 경우 아무 동작 X
		return;
	else
	{
		MyCharac->EquipWeapon((MyCharac->GetWeaponInventory())[index]); // 현재 장착중인 무기와 다른 무기를 선택할 경우 무기 교체
		AMyBasicCharacter* TempMyCharac = Cast<AMyBasicCharacter>(MyCharac);
		if (TempMyCharac)
			TempMyCharac->PlaySound("WeaponChange"); // 무기 교체 소리 출력
	}
}

/*
void UUI_Inventory_Widget::SpawnSlots()
{
	AController_StartMenu* controller = Cast<AController_StartMenu>(GetOwningPlayer());

	UUserWidget* slotWidget = controller->uiItemSlotWidget;

	for (int i = 0; i < 8; i++)
	{
		slotWidget = CreateWidget<UUserWidget>(GetWorld());
		GridPanel_ItemSlots->AddChildToGrid(slotWidget);
		MyItemSlot->AddToViewport();
	}





	//GridPanel_ItemSlots->AddChildToGrid(tempWidget);
	//UUniformGridSlot* slotBox = Cast<UUniformGridSlot>(GetWidgetFromName(FName("GridPanel_ItemSlots")));
	//UHorizontalBox* slotBox = Cast<UHorizontalBox>(GetWidgetFromName(FName("HorizontalBox_01")));



	//for (int i = 0; i < 5; i++)
	//{
		//uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
		//GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);

		//UUserWidget* slotWidget = WidgetTree->ConstructWidget<UUI_ItemSlot_Widget>(MyWidgetClass);

		//slotBox->AddChild(slotWidget);
	//}

	//GridPanel_ItemSlots->AddChildToGrid();


	//static ConstructorHelpers::FClassFinder<UUserWidget> myItemSlot(TEXT("/Game/_My/UI/ItemSlot_BP"));
	//if (myItemSlot.Succeeded())
	//{
	//	uiItemSlotBPClass = myItemSlot.Class;
	//}

	//if (uiItemSlotBPClass)
	//{
	//	uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
	//	if (uiItemSlotWidget)
	//	{
	//		//if (GridPanel_ItemSlots)
	//		//{
	//		//	GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);
	//		//}
	//		uiItemSlotWidget->AddToViewport();
	//	}
	//}

	//auto GridPanel_ItemSlots = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	//if (GridPanel_ItemSlots)
	//{
	//	auto uiItemSlotBPClass = WidgetTree->ConstructWidget<UUserWidget>(UUserWidget::StaticClass());
	//	GridPanel_ItemSlots->AddChild(uiItemSlotBPClass);
	//}

}
*/
